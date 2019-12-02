module SRAM_Control_module
(
       CLK,RSTn,
		 Ready_Sig, Column_Addr_Sig, Row_Addr_Sig,
		 H2L_Sig_V, L2H_Sig_V,
		 L2H_Sig_H,
		 L2H_Sig_P,
		 Y_Data,
       SRAM_WE, SRAM_CE, SRAM_OE, SRAM_LB, SRAM_UB,
		 ADDR,DATA,
		 Red_Sig, Green_Sig, Blue_Sig

); 
input CLK,RSTn;
input Ready_Sig; 
input [10:0]Column_Addr_Sig;
input [10:0]Row_Addr_Sig;
input H2L_Sig_V,L2H_Sig_V,L2H_Sig_H,L2H_Sig_P;
input [7:0]Y_Data;


output SRAM_WE,SRAM_CE,SRAM_OE,SRAM_LB,SRAM_UB;
output [17:0]ADDR;
output Red_Sig, Green_Sig, Blue_Sig;


inout [7:0]DATA;

/************************************************

parameter T16p64ms=20'd1664000;


/*****************¼ÆÊ±***************************
reg [17:0]Count;
always @ (posedge CLK or negedge RSTn)
       if(!RSTn)
		        Count<=18'd0;
		 else if(Count==T16p64ms)
              Count<=18'd0;
		 else 
		        Count<=Count+1'b1;

/************************************************/
reg SRAM_WE_r;
reg SRAM_CE_r;
reg SRAM_OE_r;
reg SRAM_LB_r;
reg SRAM_UB_r;
reg [3:0]i;
reg  Done_VGA_R;
reg  Done_Collect_R;

always @ (posedge CLK or negedge RSTn)
       if(!RSTn)
		   begin
			     SRAM_WE_r<=1'd1;
				  SRAM_CE_r<=1'd1;
				  SRAM_OE_r<=1'd1;
				  SRAM_LB_r<=1'd1;
				  SRAM_UB_r<=1'd1;
				  i<=4'd0;  
				  Done_VGA_R<=1'd0;
				  Done_Collect_R<=1'd0;
			end
		 else if(1)
		   case(i)
			   0:
				if(H2L_Sig_V)begin  i<=i+1'b1;   end
				else
			   	begin
						  SRAM_WE_r<=1'd0;
						  SRAM_CE_r<=1'd0;
						  SRAM_OE_r<=1'd1;
						  SRAM_LB_r<=1'd0;
						  SRAM_UB_r<=1'd1;                   // data in
						  Done_VGA_R<=1'd1;
						  Done_Collect_R<=1'd0;
						//  ADDR_r<=18'd0;  
					end
	         1,2,3:
		   	if(H2L_Sig_V)begin   i<=i+1'b1;     end
				else
					begin
						  SRAM_WE_r<=1'd1;
						  SRAM_CE_r<=1'd0;
						  SRAM_OE_r<=1'd0;
						  SRAM_LB_r<=1'd0;
						  SRAM_UB_r<=1'd1;                   // data out
					     Done_VGA_R<=1'd0;
						  Done_Collect_R<=1'd1;
					end
				4:         begin  i<=4'd0;  end 
			 endcase
				 
/*************************************************/

assign SRAM_WE=SRAM_WE_r;
assign SRAM_CE=SRAM_CE_r;
assign SRAM_OE=SRAM_OE_r;
assign SRAM_LB=SRAM_LB_r; 
assign SRAM_UB=SRAM_UB_r;


/***************************************************/
reg [8:0]VSYNC_Count;

always @ (posedge CLK or negedge RSTn)
       if(!RSTn)
		       begin
		             VSYNC_Count<=9'd0;						
				 end
		 else if(H2L_Sig_V )
		       begin
						 VSYNC_Count<=9'd0;				
				 end
		 else if(HREF_Count==640 && Done_VGA_R)
			    begin
						 VSYNC_Count<=VSYNC_Count+1'b1;
			    end
		
/****************************************************/
reg [9:0]HREF_Count;
reg [17:0]ADDR_r;

always @ (posedge CLK or negedge RSTn)

       if(!RSTn)
		      begin
                 	 ADDR_r<=18'd0;
					    HREF_Count<=10'd0;
				end	
        else if(HREF_Count==640)
			    begin
                   HREF_Count<=10'd0;
			    end				
		  else if(L2H_Sig_H && L2H_Sig_P && Done_VGA_R)
				 begin
					HREF_Count<=HREF_Count+1'd1;
					ADDR_r<=ADDR_r+1'd1;
				 end 
		  else if(Done_Collect_R==1)
		         ADDR_r<=18'd0;
/*****************************************************/

	 reg isRectangle;
	 
	 always @ ( posedge CLK or negedge RSTn )
	     if( !RSTn )
		      isRectangle <= 1'b0;
		  else if((Column_Addr_Sig >= 11'd0 && Column_Addr_Sig < 640 )&& Row_Addr_Sig < 11'd240 && Done_Collect_R) 
            isRectangle <= 1'b1;
		  else
		      isRectangle <= 1'b0;
				


/************************************/
	reg [17:0]ADDR_R;
	reg [10:0]m;
	always@(posedge CLK or negedge RSTn)
	    if(!RSTn)
		   begin
		        m<=11'd0;
			     ADDR_R<=18'd0;
			end
		 else if(Ready_Sig&&Row_Addr_Sig<240 && Done_Collect_R )
		   begin
		        m<=Row_Addr_Sig[10:0]; 
				  ADDR_R<=(m<<9+m<<7+n);
			end
			
/************************************/
	
	reg[10:0]n;
	always@(posedge CLK or negedge RSTn)
	   if(!RSTn)
		   n<=11'd0;
		else if(Ready_Sig&&Column_Addr_Sig<640 && Done_Collect_R)
		   n<=Column_Addr_Sig[10:0];
/*****************************************************/			
wire [7:0]DataOut;
assign DATA=Done_VGA_R ? Y_Data : 8'bzz;
assign DataOut=Done_Collect_R ? DATA : DataOut;
assign ADDR=Done_Collect_R ? ADDR_R : ADDR_r;
/*****************************************************/
reg data;
always @ (posedge CLK or negedge RSTn)
         if(!RSTn)
			       data<=1'd0;
         else if(Done_Collect_R)
						begin			
							   if(DataOut<=8'b01110110)
										 data<=1'd0;
								else			 
										 data<=1'd1;
						end
			else
			 data<=1'd0; 
			
/*******************************************************/

assign Red_Sig=(Ready_Sig && isRectangle && Done_Collect_R)? data : 1'b0;
assign Green_Sig=(Ready_Sig && isRectangle && Done_Collect_R) ? data : 1'b0;
assign Blue_Sig=(Ready_Sig && isRectangle && Done_Collect_R) ? data : 1'b0;

/*******************************************************/





endmodule













