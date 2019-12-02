module sram_test
(clk,rst,sw1,sw2,DATA,ADDR,CE,OE,WE,led);

input sw1;              //д��������ź�
input sw2;              //����������ź�
input clk;              //����ʱ���ź�
input rst;              //��λ�ź�
inout[7:0] DATA;	      //��������				
output[17:0] ADDR;      //��ַ����
output reg CE;          //Ƭѡʹ���ź�
output reg OE;          //���ʹ���ź�
output reg WE;          //дʹ���ź�   
output[3:0] led;        //�������ָʾ��

wire [7:0] data_in;     //�������
reg [7:0] data_out;     //��������
reg [7:0] rd_reg;       //��������Ĵ���
reg [17:0] addr_num;    //�����ַ�Ĵ���
reg [17:0] addr_reg;    //��ַ�Ĵ���
reg link_wr;            //д�źżĴ���
reg link_rd;            //���źżĴ���
reg link_addr;          //��ַ�źżĴ���
reg WF;                 //д�ź�״̬��־
reg RF;                 //���ź�״̬��־       
reg [5:0] state;        //״̬��־
reg [1:0] num;

parameter IDLE      =6'b000_001,                //��ʼ״̬
		    READY     =6'b000_010,                //׼��״̬
		    WR_ADDRNEW=6'b000_100,                //д����״̬
		    WR_DATANEW=6'b001_000,                //д��ַ״̬
		    RD_ADDRNEW=6'b010_000,                //������״̬
		    RD_DATANEW=6'b100_000;                //����ַ״̬

parameter YES = 1'b1,                           //��
		    NO  = 1'b0;                           //��
		
assign DATA=link_wr?data_out:8'bzz;             //����������
assign ADDR=link_addr?addr_reg:18'bzz;          //��ַ������
assign data_in=link_rd?DATA:data_in;            //������������
assign led=rd_reg[3:0];

always @(posedge clk or negedge rst)                                                                       
if (!rst)                                       //Ƭѡδѡ����ʼ��
		begin
		link_wr<=NO;
		link_rd<=NO;
		link_addr<=NO;
		WF<=0;
		RF<=0;
		rd_reg<=0;
		data_out<=0;
		addr_reg<=0;
		addr_num<=0;
		CE<=1;
		OE<=1;
		WE<=1;
		state<=IDLE;
		num<=2'b0;
		end
else 
	begin
		casex (state)
			 IDLE:  begin                                //��ʼ��
						link_wr<=NO;
						link_rd<=NO;
						link_addr<=NO;
						addr_reg<=0;
						CE<=0;
						OE<=1;
						WE<=1;
					if (sw1)			//��д�����źţ������׼��д״̬
							begin
								WF<=1;
								RF<=0;
								state<=READY;
							end
					if (sw2)                              //�ж������źţ������׼����״̬
							begin
								WF<=0;
								RF<=1;
								state<=READY;
							end
					else                                       // �������źţ�������ʼ״̬               
							begin
								WF<=0;
								RF<=0;
								state<=IDLE;
							end
					  end
			READY:  begin                    //׼��״̬
					  if (WF==YES)      
						 state<=WR_ADDRNEW;
					  if (RF==YES)
						 state<=RD_ADDRNEW;
					  end
			WR_ADDRNEW: begin
							//addr_num<=19'b011;
					/*	if (addr_reg==addr_num)                  //�����Ҫд���ַ�ı�ţ����������
								begin
										case(num)
											0: addr_num<=18'b000;
											1: addr_num<=18'b001;
											2: addr_num<=18'b010;
										default: addr_num<=0;
										endcase
								
										link_addr<=YES;		          //��ַ�����ź�����	
										state<=WR_DATANEW;
								end
						else            */                   //����                                      
						//		begin
						         WE<=0;               
								   CE<=0;
									link_addr<=YES;	
									addr_reg<=18'd1;    //��ַ��1
									state<=WR_ADDRNEW;          //����д����    ��������д������         
						//		end
						  end
			WR_DATANEW: begin
							/*	case(num)
									0: data_out<=8'b00110011;
									1: data_out<=8'b11111111;
									2: data_out<=8'b11001100;
								default: data_out<=0;
								endcase   */
								
								data_out<=8'b10101010;	
								WE<=0;               
								CE<=0;
								link_wr<=YES;                        //д��������
					//			num<=num+1;
								state<=IDLE;
							end
			RD_ADDRNEW: begin
							//addr_num<=19'b000;
							addr_reg<=18'd1;
				/*			if(addr_reg==addr_num)	
								begin
									link_addr<=YES;					
									state<=RD_DATANEW;                   //�������ַ״̬
								end
							else    */
			//					begin
			                  OE<=0;                                               //������
								   CE<=0;
			                  link_addr<=YES;
									state<=RD_DATANEW;
			//						addr_reg<=addr_reg+18'b1;      //��ַ��1
			//						state<=RD_ADDRNEW;
			//					end
							end  
			RD_DATANEW:	begin
								OE<=0;                                               //������
								CE<=0;
								link_rd<=YES;
								rd_reg<=data_in;						
								state<=IDLE;
							end    
		//	default:	state<=IDLE;
		endcase
	end 			
endmodule
