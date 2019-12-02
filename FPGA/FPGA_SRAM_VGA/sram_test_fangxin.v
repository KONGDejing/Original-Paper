`timescale 1ns/1ps
module sram_test_fangxin
(
    input CLK,     //150M
	 input RSTn,
	 

	 output[17:0]sram_addr,
	 output sram_wr_n,
	 output sram_ce_n,
	 inout[7:0]sram_data,
	 
	 output HSYNC,
    output VSYNC,
	 output [2:0]RGB_Sig,
	 
	 output led
);
/**************延时***********************
reg [2:0]delay;
reg [17:0]count;
always @(posedge CLK or negedge RSTn)
      if(!RSTn)
		   delay<=3'd0;
		else if(delay==8)
		    begin delay<=3'd0;count<=count+1;end
		else 
		   delay<=delay+1'b1;
********************VGA同步****************************/

reg [9:0]C1;
reg [9:0]C2;
reg rH,rV;
reg sram_ce_r; 
	 always @ ( posedge CLK or negedge RSTn )
	     if( !RSTn )
		      begin
				    C1 <= 10'd0;
					 C2 <= 10'd0;
					 rH <= 1'b1;
					 rV <= 1'b1;
					 sram_ce_r<=1'b1;
				end
		  else 
		      begin
				    
					 if( C1 == 800) rH <= 1'b0; 
				     else if( C1 == 96 ) rH <= 1'b1;
				     //else if( C1 == 0 ) rH <= 1'b0;
					 
					 if( C2 == 525 ) rV <= 1'b0;
					 else if( C2 == 2  ) rV <= 1'b1;
					 //else if( C2 == 0 ) rV <= 1'b0;
					 
					 if( C2 == 525 ) C2 <= 10'd1;
					 else if( C1 == 800 ) C2 <= C2 + 1'b1;
					 
				     if( C1 == 800 ) C1 <= 11'd1;
					 else if(count==5)C1 <= C1 + 1'b1;				 
					 
				end
assign HSYNC = rH;
assign VSYNC = rV;
assign sram_ce_n=1'b0;	 //SRAM使能
/********************VGA扫描*********************************/
	 
	 parameter _X = 10'd640, _Y = 10'd240, _XOFF = 10'd0, _YOFF = 10'd0; 
	 
/**************************************/
    reg isRectangle;
    reg [17:0]x,y;
	 reg [17:0]ADDR_R;
    reg [4:0]j;

    always @ ( posedge CLK or negedge RSTn )
	     if( !RSTn )
		      begin
				    x <= 18'd0;
					 y <= 18'd0;
				    ADDR_R<=18'd0;
					 j<=5'd0;					
				end
			else
			case(j)
				0:
			   begin				
				    // step 1 : compute data address and index-n
					 if( (C1 > 96 + 48 + _XOFF && C1 <= 96 + 48 + _XOFF +_X) && 
					     (C2 > 2 + 33 + _YOFF && C2 <= 2 + 33 + _YOFF + _Y) && VGA_r)
					     begin 							 
								isRectangle <= 1'b1;
								x <= C1 - _XOFF - 96 - 48 - 1; 
								y <= C2 - _YOFF - 2 - 33 - 1;	
		                  j<=j+1'b1;
	                     ADDR_R <= (y << 9 +  y <<7) + x;		//取地址	（图片的大小640*240）				
						  end				 
					 else                       
					    begin isRectangle <= 1'b0;  j<=j+1'b1;end 
		       end
				 1:begin j<=j+1'b1;end   //address = y*640+x
             2,3:begin j<=j+1'b1; end				 
				 4:begin   j<=1'b0; end
			endcase
/******************count计数*******************/

reg [4:0]count;
always @(posedge CLK or negedge RSTn)
  if(!RSTn)
     begin count<=5'd0; end
  else if(count==5'd5)
      count<=5'd1;
  else
	   count<=count+1'b1;
//----------------------------------------------

reg [7:0]wr_data;
reg [7:0]rd_data;
reg [17:0]addr_r;

reg sram_wr_req;       //sram写请求
reg sram_rd_req;       //sram读请求
reg [4:0]i;
reg led_r;
reg VGA_r;             //开始显示数据的标志位


always @(posedge CLK or negedge RSTn)
     if(!RSTn)
	  begin sram_wr_req<=1'b0;sram_rd_req<=1'b0;wr_data<=8'd0;addr_r<=18'd0;i<=5'd0;VGA_r<=1'b0;rRGB<=3'b000;led_r<=1'b0;end
     else
	   case(i)
  //    0:
	//	begin i<=i+1'b1;end
      0:
      begin sram_wr_req<=1'b1;i<=i+1'b1;end
		1:
		begin sram_wr_req<=1'b0;i<=i+1'b1;wr_data<=8'b00101111;addr_r<=addr_r+1'b1;end
		2,3:
		begin i<=i+1'b1;end
		4:
		begin 
		  if(addr_r<76800) i<=5'd0;
		  else if(addr_r>=18'd76800 && addr_r<18'd153600)begin i<=i+1'b1; end 
		end
		5:
      begin sram_wr_req<=1'b1;i<=i+1'b1;end
		6:
		begin sram_wr_req<=1'b0;i<=i+1'b1;wr_data<=8'b11101111;addr_r<=addr_r+1'b1;end
		7,8:
		begin i<=i+1'b1;end
		9:
		begin 
		  if(addr_r>=18'd153600)
		  begin i<=i+1'b1;VGA_r<=1'b1;end
		  else i<=5'd5;
		end
		10:
		begin sram_rd_req<=1'b1;i<=i+1'b1;end
		11:
		begin sram_rd_req<=1'b0;i<=i+1'b1;addr_r<=ADDR_R ;end 
		12,13:
		begin i<=i+1'b1;end
		14:
		begin 
			i<=5'd10;			    
			if(rd_data>=8'b01010101)begin led_r<=1'b1;rRGB<=3'b111; end  //led灯亮,另外相应的VGA相应地址ADDR_R处的值应该为3'b111;
			else 
			begin led_r<=1'b0;rRGB<=3'b000; end                 //灯灭
		end
	   endcase
      		
reg [2:0]rRGB;
	
assign led=led_r;	  
assign sram_addr=addr_r;
assign sram_ce_n=1'b0;
assign RGB_Sig=isRectangle ? rRGB:3'b000;	  
	  


/*-------------------两段式状态机------------------*/

`define DELAY_20NS    (cnt==3'd1)       //这一块只是修改了cnt计数，我的sram是IS61LV25616,其余的是参考特权的SRAM两步状态机
reg [2:0]cnt;

always @(posedge CLK or negedge RSTn)
     if(!RSTn) cnt<=3'd0;
     else if(cstate==IDLE)cnt<=3'd0;
	  else cnt<=cnt+1'b1;
//-------------------------------------------------

parameter IDLE =4'd0,
          WRT0 =4'd1,
			 WRT1 =4'd2,
			 REA0 =4'd3,
			 REA1 =4'd4;
reg [3:0]cstate,nstate;

always @(posedge CLK or negedge RSTn)
    if(!RSTn)cstate<=IDLE; 
	 else cstate<=nstate;
	 
always @(cstate or sram_wr_req or sram_rd_req or cnt)
    case(cstate)
	      IDLE: if(sram_wr_req)nstate<=WRT0;
			      else if(sram_rd_req)nstate<=REA0;
					else nstate<=IDLE;
			WRT0: if(`DELAY_20NS) nstate<=WRT1;
			      else nstate<=WRT0;
			WRT1: nstate<=IDLE;
			REA0: if(`DELAY_20NS) nstate<=REA1;
			      else nstate<=REA0;
			REA1: nstate<=IDLE;
		default: nstate<=IDLE;
	endcase
/******************读数据**************************/
always @(posedge CLK or negedge RSTn)
    if(!RSTn)rd_data<=8'd0;
    else if(cstate==REA1)rd_data<=sram_data;		
//----------------读写控制位--------------------------------	
reg sdlink;
always @(posedge CLK or negedge RSTn)
    if(!RSTn)sdlink<=1'b0;
	 else
	    case(cstate)
		     IDLE: if(sram_wr_req)sdlink <=1'b1;
			        else if(sram_rd_req)sdlink<=1'b0;
					  else sdlink<=1'b0;
			  WRT0: sdlink<=1'b1;
			  default: sdlink<=1'b0;
			  endcase
			  
assign sram_data = sdlink ? wr_data : 8'hzz;
assign sram_wr_n = ~sdlink;   

/*-------------------------------------------------

reg [2:0]j;
reg [2:0]rRGB; 
reg [2:0]rRGB_Sig;
always @(posedge CLK or negedge RSTn)
	if(!RSTn)begin rd_data<=8'd0;rRGB<=3'b000;j<=3'd0;end
	else   
	  case(j)
	  0: if(cstate==REA1)begin rd_data<=sram_data;j<=j+1'b1;end
	  1: if(VGA_r)
	       begin  
			    if(rd_data<=8'b01111111)begin j<=j+1'b1;rRGB<=3'b000; end
             else  begin rRGB<=3'b111;j<=j+1'b1; end
			 end
		  else 
		    begin rRGB<=3'b000;j<=j+1'b1;end
	  2:begin j<=1'b0; rRGB_Sig<=( isRectangle & VGA_r)? rRGB : 3'b000;end

	  endcase
  
			


		  
          	  
  */

endmodule


