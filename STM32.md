引脚开启方式
    RCC_APB2PeriphClockCmd(RCC_APB2Preiph_GPIOX, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_XXX;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_XX;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIO_X, &GPIO_Init_Structure);

设置引脚输出
    GPIO_SetBits(GPIO_X, GPIO_Pin_X);