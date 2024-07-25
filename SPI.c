typedef struct
{
    uint16_t SPI_Direction;         /*!< 传输方向，两向全双工，单向接收等*/
    uint16_t SPI_Mode;              /*!< 模式选择，确定主机还是从机 */
    uint16_t SPI_DataSize;          /*!< 数据大小，8位还是16位 */
    uint16_t SPI_CPOL;              /*!< 时钟极性选择 */
    uint16_t SPI_CPHA;              /*!< 时钟相位选择 */
    uint16_t SPI_NSS;               /*!< 片选是硬件还是软件*/
    uint16_t SPI_BaudRatePrescaler; /*!< 分频系数 */
    uint16_t SPI_FirstBit;          /*!< 指定数据传输是从MSB还是LSB位开始的。M
             SB就是二进制第一位，LSB就是最后一位 */
    uint16_t SPI_CRCPolynomial;     /*!< CRC校验 ，设置 CRC 校验多项式，提高通
        信可靠性，大于 1 即可*/
} SPI_InitTypeDef;

void SPI2_Init(){
    GPIO_InitTypeDef GPIO_InitStructure;
    SPI_InitTypeDef SPI_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_SetBits(GPIOB, GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);

    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;              // 双向全双工
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;                                   // 主机模式
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;                               // 数据大小
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;                                     // 休息时高电平，低电平触发
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;                                    // 第二个由高变低的跳变时数据被采样，第一个由高到低跳变时发送数据
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;                                       // 软件控制NSS
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;  
    SPI_InitStructure.SPI_CRCPolynomial = 7;                                        // CRC校验位
    SPI_Init(SPI2, &SPI_InitStructure);

    SPI_Cmd(SPI2, ENABLE);

    SPI2_ReadWriteByte(0xFF);        
}