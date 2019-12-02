module sram_test
(clk,rst,sw1,sw2,DATA,ADDR,CE,OE,WE,led);

input sw1;              //写允许控制信号
input sw2;              //读允许控制信号
input clk;              //输入时钟信号
input rst;              //复位信号
inout[7:0] DATA;	      //数据总线				
output[17:0] ADDR;      //地址总线
output reg CE;          //片选使能信号
output reg OE;          //输出使能信号
output reg WE;          //写使能信号   
output[3:0] led;        //输出数据指示灯

wire [7:0] data_in;     //数据输出
reg [7:0] data_out;     //数据输入
reg [7:0] rd_reg;       //数据输出寄存器
reg [17:0] addr_num;    //输入地址寄存器
reg [17:0] addr_reg;    //地址寄存器
reg link_wr;            //写信号寄存器
reg link_rd;            //读信号寄存器
reg link_addr;          //地址信号寄存器
reg WF;                 //写信号状态标志
reg RF;                 //读信号状态标志       
reg [5:0] state;        //状态标志
reg [1:0] num;

parameter IDLE      =6'b000_001,                //初始状态
		    READY     =6'b000_010,                //准备状态
		    WR_ADDRNEW=6'b000_100,                //写数据状态
		    WR_DATANEW=6'b001_000,                //写地址状态
		    RD_ADDRNEW=6'b010_000,                //读数据状态
		    RD_DATANEW=6'b100_000;                //读地址状态

parameter YES = 1'b1,                           //真
		    NO  = 1'b0;                           //假
		
assign DATA=link_wr?data_out:8'bzz;             //数据线连接
assign ADDR=link_addr?addr_reg:18'bzz;          //地址线连接
assign data_in=link_rd?DATA:data_in;            //数据总线连接
assign led=rd_reg[3:0];

always @(posedge clk or negedge rst)                                                                       
if (!rst)                                       //片选未选，初始化
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
			 IDLE:  begin                                //初始化
						link_wr<=NO;
						link_rd<=NO;
						link_addr<=NO;
						addr_reg<=0;
						CE<=0;
						OE<=1;
						WE<=1;
					if (sw1)			//有写允许信号，则进入准备写状态
							begin
								WF<=1;
								RF<=0;
								state<=READY;
							end
					if (sw2)                              //有读允许信号，则进入准备读状态
							begin
								WF<=0;
								RF<=1;
								state<=READY;
							end
					else                                       // 无允许信号，则进入初始状态               
							begin
								WF<=0;
								RF<=0;
								state<=IDLE;
							end
					  end
			READY:  begin                    //准备状态
					  if (WF==YES)      
						 state<=WR_ADDRNEW;
					  if (RF==YES)
						 state<=RD_ADDRNEW;
					  end
			WR_ADDRNEW: begin
							//addr_num<=19'b011;
					/*	if (addr_reg==addr_num)                  //如果是要写入地址的编号，则结束返回
								begin
										case(num)
											0: addr_num<=18'b000;
											1: addr_num<=18'b001;
											2: addr_num<=18'b010;
										default: addr_num<=0;
										endcase
								
										link_addr<=YES;		          //地址控制信号允许	
										state<=WR_DATANEW;
								end
						else            */                   //不是                                      
						//		begin
						         WE<=0;               
								   CE<=0;
									link_addr<=YES;	
									addr_reg<=18'd1;    //地址加1
									state<=WR_ADDRNEW;          //返回写数据    ；；连续写入数据         
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
								link_wr<=YES;                        //写控制允许
					//			num<=num+1;
								state<=IDLE;
							end
			RD_ADDRNEW: begin
							//addr_num<=19'b000;
							addr_reg<=18'd1;
				/*			if(addr_reg==addr_num)	
								begin
									link_addr<=YES;					
									state<=RD_DATANEW;                   //进入读地址状态
								end
							else    */
			//					begin
			                  OE<=0;                                               //读允许
								   CE<=0;
			                  link_addr<=YES;
									state<=RD_DATANEW;
			//						addr_reg<=addr_reg+18'b1;      //地址加1
			//						state<=RD_ADDRNEW;
			//					end
							end  
			RD_DATANEW:	begin
								OE<=0;                                               //读允许
								CE<=0;
								link_rd<=YES;
								rd_reg<=data_in;						
								state<=IDLE;
							end    
		//	default:	state<=IDLE;
		endcase
	end 			
endmodule
