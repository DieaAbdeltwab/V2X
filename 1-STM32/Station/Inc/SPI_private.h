


#ifndef  SPI_PRIVATE_H
#define  SPI_PRIVATE_H
/************************************************************************************/
/***************************** Register Bits ****************************************/
/************************************************************************************/
#define  SPI_CR1_CPHA              0
#define  SPI_CR1_CPOL              1
#define  SPI_CR1_MSTR              2
#define  SPI_CR1_BR                3
#define  SPI_CR1_SPE               6
#define  SPI_CR1_LSBFIRST          7
#define  SPI_CR1_SSI               8
#define  SPI_CR1_SSM               9
#define  SPI_CR1_RXONLY            10
#define  SPI_CR1_DFF               11

#define  SPI_CR2_RXDMAEN            0
#define  SPI_CR2_TXDMAEN            1
#define  SPI_CR2_SSOE               2
#define  SPI_CR2_RXNEIE             6
#define  SPI_CR2_TXEIE              7

#define  SPI_SR_BSY                 7
#define  SPI_SR_RXNE                0
#define  SPI_SR_TXE                 1


/************************************************************************************/
/***************************** Mask *************************************************/
/************************************************************************************/
#define  SPI_CPHA_MASK            	    0b1
#define  SPI_CPOL_MASK              	0b1
#define  SPI_MSTR_MASK                  0b1
#define  SPI_BR_MASK                    0b111
#define  SPI_SPE_MASK                   0b1
#define  SPI_LSBFIRST_MASK              0b1
#define  SPI_SSI_MASK                   0b1
#define  SPI_SSM_MASK                   0b1
#define  SPI_RXONLY_MASK                0b1
#define  SPI_DFF_MASK                   0b1

#define  SPI_RXDMAEN_MASK               0b1
#define  SPI_TXDMAEN_MASK               0b1
#define  SPI_SSOE_MASK                  0b1
#define  SPI_RXNEIE_MASK                0b1
#define  SPI_TXEIE_MASK                 0b1
/************************************************************************************/
/***************************** Flags Mask *******************************************/
/************************************************************************************/
#define  SPI_BSY_FLAG                   1
#define  SPI_TXE_FLAG                   0
#define  SPI_RXNE_FLAG                  0
/************************************************************************************/
/************************************************************************************/
/************************************************************************************/





#endif
