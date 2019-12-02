module SRAM_Control_module_1
(
       CLK,RSTn,
		 H2L_Sig_V, L2H_Sig_V,
		 L2H_Sig_H,
		 L2H_Sig_P,
		 qC1,
	    qC2,
		 RGB_Sig,
		 Y_Data,
       SRAM_WE, SRAM_CE, SRAM_OE, SRAM_LB, SRAM_UB,
		 ADDR,DATA,


); 

input CLK,RSTn;
input [10:0]qC1;
input [9:0]qC2;

input H2L_Sig_V,L2H_Sig_V,L2H_Sig_H,L2H_Sig_P;
input [7:0]Y_Data;


output SRAM_WE,SRAM_CE,SRAM_OE,SRAM_LB,SRAM_UB;
output [17:0]ADDR;
output [2:0]RGB_Sig;



inout [7:0]DATA;

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
						  ADDR_r<=18'd0; 
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
/********************VGAɨ��*********************************/
	 
	 parameter _X = 8'd640, _Y = 8'd240, _XOFF = 10'd0, _YOFF = 10'd25; 
	 
	 /**************************************/
    reg isRectangle;
    reg [9:0]x,y;
	 reg [17:0]ADDR_R;
	 reg [2:0]rRGB;

    always @ ( posedge CLK or negedge RSTn )
	     if( !RSTn )
		      begin
				    x <= 10'd0;
					 y <= 10'd0;
				    ADDR_R<=18'd0;
				    rRGB <= 3'd0;
				end
			else
			   begin
				
				    // step 1 : compute data address and index-n
					 if( (qC1 > 152 + 232 + _XOFF && qC1 <= 152 + 232 + _XOFF +_X) && 
					     (qC2 > 3 + 28 + _YOFF && qC2 <= 3 + 28 + _YOFF + _Y) && Done_Collect_R)
					     begin 
						      isRectangle <= 1'b1;
						      x = qC1 - _XOFF - 152 - 232 - 1; 
						      y = qC2 - _YOFF - 3 - 28 - 1;
					         ADDR_R <= (y << 9 +  y <<7) + x ; 
					     end
					 else 
					         isRectangle <= 1'b0;
		       end
/*****************************************************/

			
wire [7:0]DataOut;
assign DATA=Done_VGA_R ? Y_Data : 8'bzz;
assign DataOut=DATA;
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

assign Red_Sig=( isRectangle && Done_Collect_R)? data : 1'b0;
assign Green_Sig=( isRectangle && Done_Collect_R) ? data : 1'b0;
assign Blue_Sig=( isRectangle && Done_Collect_R) ? data : 1'b0;

/*******************************************************/





endmodule













