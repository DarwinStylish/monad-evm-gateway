#include <stdio.h>
#include <assert.h>
#include "adapter_monad.h"

int main() {
    printf("[*] Running Monad EVM Adapter Verification...\n");

    // Allocate the full 76 bytes for the EVM log
    uint8_t raw_log[76] = {0};
    monad_evm_log_t* mock_log = (monad_evm_log_t*)raw_log;
    mock_log->amount_in = 1000;
    mock_log->amount_out = 5000;

    event_t out;
    assert(parse_monad_evm(raw_log, &out));

    printf("[+] Successfully parsed Monad EVM log.\n");
    printf("[+] Calculated Price: %f\n", to_double(out.price));

    return 0;
}
