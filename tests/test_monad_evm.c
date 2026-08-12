#include <stdio.h>
#include <assert.h>
#include "adapter_monad.h"

int main() {
    printf("[*] Running Monad EVM Adapter Verification...\n");

    /* Happy path: valid swap log */
    uint8_t raw_log[76] = {0};
    monad_evm_log_t* mock_log = (monad_evm_log_t*)raw_log;
    mock_log->amount_in = 1000;
    mock_log->amount_out = 5000;

    event_t out;
    assert(parse_monad_evm(raw_log, &out));
    assert(out.venue_id == VENUE_MONAD);
    assert(out.instrument_id == MONAD_DEFAULT_INSTRUMENT_ID);

    printf("[+] Successfully parsed Monad EVM log.\n");
    printf("[+] Calculated Price: %f\n", to_double(out.price));

    /* Negative test: zero amount_in (div-by-zero guard) */
    uint8_t bad_log[76] = {0};
    monad_evm_log_t* bad = (monad_evm_log_t*)bad_log;
    bad->amount_in = 0;
    bad->amount_out = 5000;
    assert(parse_monad_evm(bad_log, &out) == false);
    printf("[+] Zero amount_in correctly rejected.\n");

    printf("\n[SUCCESS] Monad EVM tests passed.\n");
    return 0;
}
