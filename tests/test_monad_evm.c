// SPDX-License-Identifier: Apache-2.0
// Copyright 2026 Okot Darwin Clay
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <stdio.h>
#include <assert.h>
#include "adapter_monad.h"

int main() {
    printf("[*] Running Monad EVM Adapter Verification...\n");

    /* Happy path: valid swap log */
    monad_evm_log_t mock_log = {0};
    mock_log.amount_in = 1000;
    mock_log.amount_out = 5000;

    event_t out;
    assert(parse_monad_evm((const uint8_t*)&mock_log, sizeof(mock_log), 1, &out));
    assert(out.venue_id == VENUE_MONAD);
    assert(out.instrument_id == MONAD_DEFAULT_INSTRUMENT_ID);
    assert(out.price == from_double(5.0));

    printf("[+] Successfully parsed Monad EVM log.\n");
    printf("[+] Calculated Price: %f\n", to_double(out.price));

    /* Negative test: zero amount_in (div-by-zero guard) */
    monad_evm_log_t bad = {0};
    bad.amount_in = 0;
    bad.amount_out = 5000;
    assert(parse_monad_evm((const uint8_t*)&bad, sizeof(bad), 2, &out) == false);
    printf("[+] Zero amount_in correctly rejected.\n");

    /* Negative test: buffer too short */
    assert(parse_monad_evm((const uint8_t*)&mock_log, sizeof(mock_log) - 1, 3, &out) == false);
    printf("[+] Buffer too short correctly rejected.\n");

    printf("\n[SUCCESS] Monad EVM tests passed.\n");
    return 0;
}
