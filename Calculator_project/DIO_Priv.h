


#ifndef DIO_PRIV_H_
#define DIO_PRIV_H_



extern const DIO_PinStatus_t DIO_PinsStatusArray[TOTAL_PINS];

static void DIO_InitPin(DIO_Pin_t pin, DIO_PinStatus_t status);  // array from confg.


#endif /* DIO_PRIV_H_ */