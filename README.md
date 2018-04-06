# stm32f1-dma-usart1-rx-tx

dev kit: stm32f103c8t6

IDE: Keil MDK5

source code in the ./User, project entrance in the ./Object

function:

- usart1
- rx receive using DMA1_IT_TC5 interrupt, send the same data received using dma usart1 tx in the interrupt handler function
- tx send dma and emit DMA1_IT_TC4 interrupt when sending complete