#include "bluetooth.h"

void bluetooth_init(u32 baud)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef  NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE); //ʹ��GPIODʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);//ʹ��USART3ʱ��
 
	//���ڶ�Ӧ���Ÿ���ӳ��
	GPIO_PinAFConfig(BLUE_TX_PORT,GPIO_PinSource8,GPIO_AF_USART3); //
	GPIO_PinAFConfig(BLUE_RX_PORT,GPIO_PinSource9,GPIO_AF_USART3); //
	//USART3�˿�����
  //TX
   GPIO_InitStructure.GPIO_Pin = BLUE_TX_Pin; 
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
   GPIO_Init(BLUE_TX_PORT, &GPIO_InitStructure);
  //RX
   GPIO_InitStructure.GPIO_Pin = BLUE_RX_Pin; 
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
   GPIO_Init(BLUE_RX_PORT, &GPIO_InitStructure);
   //USART1 ��ʼ������
	USART_InitStructure.USART_BaudRate = baud;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
  
	USART_Init(USART3, &USART_InitStructure); //��ʼ������3
  USART_Cmd(USART3, ENABLE);  //ʹ�ܴ���2
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//��������ж�
	USART_ClearFlag(USART3, USART_FLAG_TC);

	//Usart1 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;//����1�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);


}



//����1�ж�

u8 tx = 0, tem=1 ;

void USART3_IRQHandler(void)
{
	u8 res = 0;
	if(USART_GetITStatus(USART3,USART_IT_RXNE) != RESET)
	{
			res = USART_ReceiveData(USART3);
			tx = res;
		if(tx==1)//�ϲ��ȡ
		{
			uart3_sendStr("s_1\r\n");
			top_grasp1();
//			place_playload1();
			
		}
		
			else if(tx==2)
			{
			  uart3_sendStr("s_2\r\n");
				top_grasp2();
//				place_playload2();

			}
			
			else if(tx==3)
			{
			  uart3_sendStr("s_3\r\n");
				top_grasp3();
//				place_playload3();

			}
			
     else if(tx==4)//�²��ȡ
   {
			uart3_sendStr("x_1\r\n");
		 under_grasp1();
		 Arm_back1();
//		 place_playload1();
    }
	 
		else	 if(tx==5)
   {
			uart3_sendStr("x_2\r\n");
		  under_grasp2();
		  Arm_back1();
//		 place_playload2();
	 }
    
		 
	else	 if(tx==6)
   {
		uart3_sendStr("x_3\r\n");
		 under_grasp3();
		 	Arm_back1();
//		 place_playload3();
    }
	 
	else  if(tx==7)//���ӹ�������
	 {
		 uart3_sendStr("r0_1\r\n");
//		 grasp_playload1();
		 First_place1();
	 }
	else if(tx==8)
	 {
		 uart3_sendStr("r0_2\r\n");
//		 grasp_playload2();
		 First_place2();
	 }
	else  if(tx==9)
	 {
		 uart3_sendStr("r0_3\r\n");
//		 grasp_playload3();
		 First_place3();
	 }
	else  if(tx==10)//0a���Ʒ��1�η���
	 {
		 uart3_sendStr("r1_1\r\n");
//		 	grasp_playload1();
		 Second_place1();
	 }
	else  if(tx==11)//0b
	 {
		 uart3_sendStr("r1_2\r\n");
//		 	grasp_playload2();
		 		 Second_place2();

	 }
	else  if(tx==12)//0c
	 {
		 uart3_sendStr("r1_3\r\n");
//		 	grasp_playload3();
		 	Second_place3();
	 }
	 else if(tx==13)// 0d ���Ʒ�ڶ��η���
	 {
		 uart3_sendStr("r2_1\r\n");
//		 grasp_playload1();
		 Third_place1();
		 
	 }
	else if(tx==14)//0e  ���Ʒ�ڶ��η���
	 {
		 uart3_sendStr("r2_2\r\n");
//		 	grasp_playload2();
		 	Third_place2();

	 }
  else if(tx==15)// 0f  ���Ʒ�ڶ��η���
	 {
		 uart3_sendStr("r2_3\r\n");
//		 	grasp_playload3();
		 	Third_place3();
	 }
	else if(tx==16)// 10  ��ά��ɨ������
	 {
		 uart3_sendStr("qr_on\r\n");
		 scan_qr_on();
		
	 }
	 else if(tx==17)//11    �ϲ���ɫ
	 {
		 uart3_sendStr("top_scan\r\n");
		 scan_block_top();
		
	 }
   else if(tx==18)// 12 �²�ʶ������
	 {
		 uart3_sendStr("under\r\n");
		 scan_block_under();
	 }
	else if(tx==19)//13 ��λ
	 {
		 uart3_sendStr("reset\r\n");
		 reset_state();
	 }
	 
	 else if(tx==21)//15
	 {
		 uart3_sendStr("middlestate\r\n");
			middle_state();
	 }
	 else if(tx==22)//16
		  {
		 uart3_sendStr("kel_value-\r\n");
			
		
	 }
	 else if(tx==23)//17ץ
	 {
		 Arm0 = 740; 
	 }
	 	 else if(tx==24)//18��
	 {
		 Arm0 = 600; 
	 }
	 
	 else if(tx==25)//19
	 {
		 uart3_sendStr("grasp3");
		// First_place_all(way1);
	 }
	 else if(tx==26)//1a
	 {
		 uart3_sendStr("zhua+\r\n"); 
		 Arm0 += 3;
		printf("Arm0 %d\n",Arm0);
		
	 }
	 else if(tx ==27)//1b
	 {
		 		uart3_sendStr("zhua-\r\n");
				Arm0 -= 3;
		printf("Arm0 %d\n",Arm0);

		 
	 }
	 else if(tx==28)//�ؽ�1����
	 {
		 uart3_sendStr("Arm1+\r\n");
		 Arm1 += tem;
		printf("Arm1 %d\n",Arm1);

	 }
	 	 else if(tx==29)//1d
	 {
		 uart3_sendStr("Arm1-\r\n");
		 Arm1 -= tem;
		printf("Arm1 %d\n",Arm1);

	 }
	 
	 //�ؽ�2����
	 	 else if(tx==30)//1e
	 {
		 uart3_sendStr("Arm2+\r\n");
		 Arm2 += tem;
		printf("Arm2 %d\n",Arm2);

	 }	
	 else if(tx==31)//1f
	 {
		 uart3_sendStr("Arm2-\r\n");
		 Arm2 -= tem;
		printf("Arm2 %d\n",Arm2);

	 }
	 //�ؽ�3����
	 	 else if(tx==32)//20
	 {
		 uart3_sendStr("Arm3+\r\n");
		 Arm3 += tem;
		printf("Arm3 %d\n",Arm3);

	 }	 else if(tx==33)//21
	 {
		 uart3_sendStr("Arm3-\r\n");
		 Arm3 -= tem;
		printf("Arm3 %d\n",Arm3);

	 }
	 //�ؽ�4����
	 	 else if(tx==34)//22
	 {
		 uart3_sendStr("Arm4+\r\n");
		 Arm4 += tem;
		printf("Arm4 %d\n",Arm4);

	 }	
	 else if(tx==35)//23
	 {
		 uart3_sendStr("Arm4-\r\n");
		 Arm4 -= tem;
		printf("Arm4 %d\n",Arm4);

	 }
	 //tem 
	 else if(tx==36)//24
	 {
		 uart3_sendStr("tem+\r\n");
		 tem += 1;
		printf("tem %d\n",tem);
//12:12:272719
		 
	 }
	  else if(tx==37)//25
	 {
		 uart3_sendStr("tem-\r\n");
		 tem -= 1;
		printf("tem %d\n",tem);
	 }
	 else if(tx==38)//26
	 {
		  uart3_sendStr("grasp_playload1");
		 	grasp_playload1();

	 }
	 else if(tx==39)//27
	 {
		  uart3_sendStr("grasp_playload2");
		 grasp_playload2();
	 }
	 else if(tx==40)//28
	 {
		  uart3_sendStr("grasp_playload3");
		 grasp_playload3();

	 }
	  else if(tx==41)//29
	 {
		  uart3_sendStr("place_playload1");
		 	place_playload1();

	 }
	 else if(tx==42)//2a
	 {
		  uart3_sendStr("place_playload2");
		 place_playload2();
	 }
	 else if(tx==43)//2b
	 {
		  uart3_sendStr("place_playload3");
		 place_playload3();

	 }
	 else if(tx==44)//2c
	 {
		  uart3_sendStr("arm_back");
		 Arm_back();

	 }
	 else if(tx==45)
	 {
		 		printf("\r\n\r\nArm0 %d\n",Arm0);
				printf("Arm1 %d\n",Arm1);
		 		printf("Arm2 %d\n",Arm2);
		    printf("Arm3 %d\n",Arm3);
		   printf("Arm4 %d\n",Arm4);



	 }
	 else if(tx==46)
	 {
		 printf("grasp_all");
		 top_grasp_choose(way1);
	 }
	  else if(tx==47)
	 {
		 printf("arm3_low2");
		 First_place_all(qr_mes,1);
	 }
			USART_ClearITPendingBit(USART3,USART_IT_RXNE);	
		
		
	}
	

	
	if(USART_ReceiveData(USART3) != '\0')//�ж��Ƿ������
	{
		
	}
	
}




