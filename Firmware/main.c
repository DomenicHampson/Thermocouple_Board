#include <xc.h>

#include "canlib/canlib.h"
#include "canlib/can.h"
#include "canlib/can_common.h"
#include "canlib/message_types.h"
#include "canlib/pic18f26k83/pic18f26k83_can.h"
#include "canlib/pic18f26k83/pic18f26k83_timer.h"
#include "canlib/util/can_tx_buffer.h"
#include "canlib/util/timing_util.h"

#include "mcc_generated_files/device_config.h"
#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/pin_manager.h"


#include "device_config.h"
#include "error_checks.h"
#include "platform.h"


static void can_msg_handler(const can_msg_t *msg);
static void send_status_ok(void);

// memory pool for the CAN tx buffer
uint8_t tx_pool[100];

volatile bool seen_can_message = false;


int main(void)
{
    // Initialize the device
    SYSTEM_Initialize();
    
    oscillator_init(); // init the external oscillator
    timer0_init(); // init our millis() function

    // Enable global interrupts
    INTCON0bits.GIE = 1;
    
    // Set up CAN TX
    TRISC0 = 0;
    RC0PPS = 0x33; // make C0 transmit CAN TX (page 267)

    // Set up CAN RX
    TRISC1 = 1;
    ANSELC1 = 0;
    CANRXPPS = 0x11; // make CAN read from C1 (page 264-265)
    
    // set up CAN module
    can_timing_t can_setup;
    can_generate_timing_params(_XTAL_FREQ, &can_setup);
    can_init(&can_setup, can_msg_handler);
    // set up CAN tx buffer
    txb_init(tx_pool, sizeof(tx_pool), can_send, can_send_rdy);

    // loop timer
    uint32_t last_millis = millis();
    uint32_t sensor_last_millis = millis();
    uint32_t last_message_millis = millis();
    

    bool heartbeat = false;

    while (1)
    {
        // Add your application code
}
