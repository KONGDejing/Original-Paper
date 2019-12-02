`timescale 1ns/1ps
module sram_test_fangxin
(
    input CLK,     //120M
	 input RSTn,
	 
	 output led,
	 output[17:0]sram_addr,
	 output sram_wr_n,
	 output sram_ce_n,
	 
	 inout[7:0]sram_data
);
/**************—” ±******************
reg [3:0]delay;

always @(posedge CLK or negedge RSTn)
      if(!RSTn)
		   delay<=4'd0;
		else 
		   delay<=delay+1'b1;
*************************************/

reg [7:0]wr_data;
reg [7:0]rd_data;
reg [17:0]addr_r;

reg sram_wr_req;
reg sram_rd_req;
reg led_r;
reg [4:0]i;
//assign sram_wr_req=(delay==4'd1);
//assign sram_rd_req=(delay==4'd5);

always @(posedge CLK or negedge RSTn)
     if(!RSTn)begin sram_wr_req<=1'b0;sram_rd_req<=1'b0;wr_data<=8'd0;addr_r<=18'd0;i<=5'd0;led_r<=1'b0;end
     else
	   case(i)
      0:
		begin i<=i+1'b1;end
      1:
      begin sram_wr_req<=1'b1;i<=i+1'b1;end
		2:
		begin sram_wr_req<=1'b0;i<=i+1'b1;wr_data<=8'b10101010;addr_r<=18'd250;end
		3,4:
		begin i<=i+1'b1;end
		
/*		4:
		begin 
		  if(addr_r<78600) i<=5'd1;
		  else if(addr_r>=18'd76800 && addr_r<18'd153600)begin i<=i+1'b1; end 
		end
		5:
      begin sram_wr_req<=1'b1;i<=i+1'b1;end
		6:
		begin sram_wr_req<=1'b0;i<=i+1'b1;wr_data<=8'b11111111;addr_r<=addr_r+1'b1;end
		7:
		begin i<=i+1'b1;end
		8:
		begin 
		  if(addr_r>=18'd153600)
		  begin i<=i+1'b1;addr_r<=18'd0;end
		  else i<=5'd5;
		end    */
		5:
		begin sram_rd_req<=1'b1;i<=i+1'b1;end
		6:
		begin sram_rd_req<=1'b0;i<=i+1'b1;addr_r<=18'd50;end 
		7,8:
		begin i<=i+1'b1;end
		9:
		begin 
			i<=5'd9;			    
			if(wr_data==rd_data)led_r<=1'b1;   //µ∆¡¡
			else led_r<=1'b0;                  //µ∆√
		end
	endcase
      		
	  
assign led=led_r;	  
assign sram_addr=addr_r;
assign sram_ce_n=1'b0;

/*------------------------------------------------
	  
always @(posedge CLK or negedge RSTn)
     if(!RSTn)led_r<=1'd0;
	  else if(delay==4'd10)
	      begin
			    if(wr_data==rd_data)led_r<=1'b1;
				 else led_r<=1'b0;
			end
assign led=led_r;

//--------------------◊¥Ã¨ª˙Ã´≤Ó¡À-----------------------------*/

`define DELAY_20NS    (cnt==3'd1)
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
			 
//------------------------------------------------


reg sdlink;

always @(posedge CLK or negedge RSTn)
    if(!RSTn)rd_data<=8'd0;
    else if(cstate==REA1)rd_data<=sram_data;	
	 
	 
	 
//------------------------------------------------	
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

//-------------------------------------------------			  
          	  


endmodule


