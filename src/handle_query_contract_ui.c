#include "plugin.h"
#include "utils.h"

static bool stakewise_deposit_ui(ethQueryContractUI_t *msg, const context_t *context) {
    strlcpy(msg->title, "Deposit", msg->titleLength);
    const uint8_t *eth_amount;
    uint8_t eth_amount_size;

    switch (msg->screenIndex) {
        case 0:
            eth_amount = msg->pluginSharedRO->txContent->value.value;
            eth_amount_size = msg->pluginSharedRO->txContent->value.length;
            // Converts the uint256 number located in `eth_amount` to its string representation and
            // copies this to `msg->msg`.
            return amountToString(eth_amount,
                                  eth_amount_size,
                                  WEI_TO_ETHER,
                                  "ETH",
                                  msg->msg,
                                  msg->msgLength);
        case 1:
            // If receiver is different from the current address, display the receiver.
            strlcpy(msg->title, "Receiver", msg->titleLength);
            // Get the string representation of the address stored in `context->receiver`. Put it in
            // `msg->msg`.
            display_eth_address(msg, context->receiver);
            return true;
        default:
            PRINTF("Received an invalid screenIndex\n");
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return false;
    }
}

static bool stakewise_burn_os_token_ui(ethQueryContractUI_t *msg, const context_t *context) {
    switch (msg->screenIndex) {
        case 0:
            strlcpy(msg->title, "OS shares", msg->titleLength);
            display_uint_decimal(msg, context->os_token_shares, 16);
            return true;

        default:
            PRINTF("Received an invalid screenIndex\n");
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return false;
    }
}

static bool stakewise_enter_exit_queue_ui(ethQueryContractUI_t *msg, const context_t *context) {
    switch (msg->screenIndex) {
        case 0:
            strlcpy(msg->title, "Vault shares", msg->titleLength);
            display_uint_decimal(msg, context->vault_shares, 32);
            return true;

        case 1:
            // If receiver is different from the current address, display the receiver.
            strlcpy(msg->title, "Receiver", msg->titleLength);
            // Get the string representation of the address stored in `context->receiver`. Put it in
            // `msg->msg`.
            display_eth_address(msg, context->receiver);
            return true;

        default:
            PRINTF("Received an invalid screenIndex\n");
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return false;
    }
}

static bool stakewise_claim_exited_assets_ui(ethQueryContractUI_t *msg, const context_t *context) {
    switch (msg->screenIndex) {
        case 0:
            strlcpy(msg->title, "Position ticket", msg->titleLength);
            display_uint_decimal(msg, context->vault_shares, 32);
            return true;

        case 1:
            strlcpy(msg->title, "Timestamp", msg->titleLength);
            display_uint_decimal(msg, context->timestamp, 32);
            return true;

        case 2:
            strlcpy(msg->title, "Exit Queue index", msg->titleLength);
            display_uint_decimal(msg, context->exit_queue_index, 32);
            return true;

        default:
            PRINTF("Received an invalid screenIndex\n");
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return false;
    }
}

static bool stakewise_liquidate_os_tokens_ui(ethQueryContractUI_t *msg, const context_t *context) {
    switch (msg->screenIndex) {
        case 0:
            strlcpy(msg->title, "OsToken shares", msg->titleLength);
            // Use `vault_shares` to store the os_token_shares, in this function
            // OsToken shares are 32 bytes.
            display_uint_decimal(msg, context->vault_shares, 32);
            return true;

        case 1:
            strlcpy(msg->title, "Owner", msg->titleLength);
            display_eth_address(msg, context->referrer);
            return true;

        case 2:
            strlcpy(msg->title, "Receiver", msg->titleLength);
            display_eth_address(msg, context->receiver);
            return true;

        default:
            PRINTF("Received an invalid screenIndex\n");
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return false;
    }
}

void handle_query_contract_ui(ethQueryContractUI_t *msg) {
    context_t *context = (context_t *) msg->pluginContext;
    bool ret = false;
    // msg->title is the upper line displayed on the device.
    // msg->msg is the lower line displayed on the device.
    // Clean the display fields.
    memset(msg->title, 0, msg->titleLength);
    memset(msg->msg, 0, msg->msgLength);

    switch (context->selectorIndex) {
        case STAKEWISE_DEPOSIT:
            ret = stakewise_deposit_ui(msg, context);
            break;

        case STAKEWISE_BURN_OS_TOKEN:
            ret = stakewise_burn_os_token_ui(msg, context);
            break;

        case STAKEWISE_ENTER_EXIT_QUEUE:
            ret = stakewise_enter_exit_queue_ui(msg, context);
            break;

        case STAKEWISE_CLAIM_EXITED_ASSETS:
            ret = stakewise_claim_exited_assets_ui(msg, context);
            break;

        case STAKEWISE_LIQUIDATE_OS_TOKENS:
            ret = stakewise_liquidate_os_tokens_ui(msg, context);
            break;

        default:
            PRINTF("Received an invalid selectorIndex\n");
    }
    msg->result = ret ? ETH_PLUGIN_RESULT_OK : ETH_PLUGIN_RESULT_ERROR;
}
