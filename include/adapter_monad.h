#ifndef ADAPTER_MONAD_H
#define ADAPTER_MONAD_H

#include "types.h"
#include <stdbool.h>

#pragma pack(push, 1)
typedef struct {
    uint64_t block_timestamp;
    uint8_t  contract_address[20];
    uint8_t  topic0[32]; 
    
    uint64_t amount_in;
    uint64_t amount_out;
} monad_evm_log_t;
#pragma pack(pop)

static inline bool parse_monad_evm(const uint8_t* memory_buffer, event_t* out_event) {
    const monad_evm_log_t* log_data = (const monad_evm_log_t*)memory_buffer;
    
    out_event->receive_timestamp_ns = log_data->block_timestamp * 1000000000ULL;
    out_event->price = fixed_div(from_double((double)log_data->amount_out), 
                                 from_double((double)log_data->amount_in));
    out_event->quantity = (fixed_t)log_data->amount_in;
    out_event->venue_id = VENUE_MONAD;
    out_event->event_type = EVENT_MARKET_TICK;
    out_event->instrument_id = 99; 
    out_event->side = 'B';
    
    return true;
}

#endif // ADAPTER_MONAD_H
