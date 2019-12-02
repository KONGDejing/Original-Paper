module SRAM_Control_module
(
       CLK,RSTn,
		 qC1,
	    qC2,
		 RGB_Sig,
       SRAM_WE, SRAM_CE, SRAM_OE, SRAM_LB, SRAM_UB,
		 ADDR,DATA


); 

input CLK,RSTn;
input [10:0]qC1;
input [9:0]qC2;



output SRAM_WE,SRAM_CE,SRAM_OE,SRAM_LB,SRAM_UB;
output [17:0]ADDR;
output [2:0]RGB_Sig;



inout [7:0]DATA;

/************************************************/

parameter _20MS=22'd2400000;

/************************************************/
reg SRAM_WE_r;
reg SRAM_CE_r;
reg SRAM_OE_r;
reg SRAM_LB_r;
reg SRAM_UB_r;
reg  Done_VGA_R;
reg  Done_Collect_R;
reg [31:0]Count;

always @ (posedge CLK or negedge RSTn)
       if(!RSTn)
		   begin
			     SRAM_WE_r<=1'd1;
				  SRAM_CE_r<=1'd1;
				  SRAM_OE_r<=1'd1;
				  SRAM_LB_r<=1'd1;
				  SRAM_UB_r<=1'd1;
				  Done_VGA_R<=1'd0;
				  Done_Collect_R<=1'd0;
				  Count<=32'd0;
			end
		 else 
		 begin 
		      if(Count>=_20MS)
			   	begin
						  SRAM_WE_r<=1'd1;
						  SRAM_CE_r<=1'd0;
						  SRAM_OE_r<=1'd0;
						  SRAM_LB_r<=1'd0;
						  SRAM_UB_r<=1'd1;                   // data out
					     Done_VGA_R<=1'd0;
						  Done_Collect_R<=1'd1;
					end
	         else
					begin
						  
						  SRAM_WE_r<=1'd0;
						  SRAM_CE_r<=1'd0;
						  SRAM_OE_r<=1'd0;
						  SRAM_LB_r<=1'd0;
						  SRAM_UB_r<=1'd1;                   // data in
						  Done_VGA_R<=1'd1;
						  Done_Collect_R<=1'd0; 
				
					end
					Count<=Count+1'b1;
	    end
/*************************************************/

assign SRAM_WE=SRAM_WE_r;
assign SRAM_CE=SRAM_CE_r;
assign SRAM_OE=SRAM_OE_r;
assign SRAM_LB=SRAM_LB_r; 
assign SRAM_UB=SRAM_UB_r;


/*************************************************/
reg [8:0]VSYNC_Count;

always @ (posedge CLK or negedge RSTn)
       if(!RSTn)
		       begin
		             VSYNC_Count<=9'd0;						
				 end
		 else if(VSYNC_Count==240 )
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
reg [7:0]Y_Data_r;

always @ (posedge CLK or negedge RSTn)

       if(!RSTn)
		      begin
                   ADDR_r<=18'b0;
					    HREF_Count<=10'd0;
				end	
        else if(HREF_Count==640)
			    begin
                   HREF_Count<=10'd0;
			    end				
		  else if(Done_VGA_R)
				 begin
					HREF_Count<=HREF_Count+1'd1;
					ADDR_r<=ADDR_r+1'b1;
				 end 
		  else 
		         ADDR_r<=18'b0;
/************************************************************/
always @(posedge CLK )
  if(ADDR_r<=17'd76800)
	    Y_Data_r<=8'd0;
	  else
	    Y_Data_r<=8'b11111111;
					
/********************VGAɨ��*********************************/
	 
	 parameter _X = 10'd640, _Y = 10'd240, _XOFF = 10'd0, _YOFF = 10'd25; 
	 
/**************************************/
    reg isRectangle;
    reg [17:0]x,y;
	 reg [17:0]ADDR_R;


    always @ ( posedge CLK or negedge RSTn )
	     if( !RSTn )
		      begin
				    x <= 18'd0;
					 y <= 18'd0;
				    ADDR_R<=18'd0;
				  
				end
			else
			   begin
				
				    // step 1 : compute data address and index-n
					 if( (qC1 > 152 + 232 + _XOFF && qC1 <= 152 + 232 + _XOFF +_X) && 
					     (qC2 > 3 + 28 + _YOFF && qC2 <= 3 + 28 + _YOFF + _Y) && Done_Collect_R)
					     begin 
						      isRectangle <= 1'b1;
						      x <= qC1 - _XOFF - 152 - 232 - 1; 
						      y <= qC2 - _YOFF - 3 - 28 - 1;
					         ADDR_R = (y << 9 +  y <<7) + x ; //address = y*640+x
					     end
					 else 
					         isRectangle <= 1'b0;
		       end
/*****************************************************/

			
wire [7:0]DataOut;
assign DATA=Done_VGA_R ? Y_Data_r : 8'bzz;
assign DataOut=Done_Collect_R ? DATA: DataOut;
assign ADDR=Done_Collect_R ? ADDR_R : ADDR_r;
/*****************************************************/
reg [2:0]rRGB;
always @ (posedge CLK or negedge RSTn)
         if(!RSTn)
			       rRGB<=3'b000;
         else if(Done_Collect_R)
						begin			
							   if(DataOut<=8'b01111111)
										 rRGB<=3'b000;
								else			 
										 rRGB<=3'b111;
						end
			else
			 rRGB<=3'b000; 
			
/*******************************************************/

assign RGB_Sig=( isRectangle && Done_Collect_R)? rRGB : 3'b000;


/*******************************************************/





endmodule













