module SRAM_Control_module
(
       CLK,RSTn,
		 H2L_Sig_V, L2H_Sig_V,
		 L2H_Sig_H,
		 L2H_Sig_P,
	    HSYNC,
	    VSYNC,
		 RGB_Sig,
		 Y_Data,
       SRAM_WE, SRAM_CE, SRAM_OE, SRAM_LB, SRAM_UB,
		 ADDR,DATA


); 

input CLK,RSTn;
input H2L_Sig_V,L2H_Sig_V,L2H_Sig_H,L2H_Sig_P;
input [7:0]Y_Data;


output SRAM_WE,SRAM_CE,SRAM_OE,SRAM_LB,SRAM_UB;
output [17:0]ADDR;
output [2:0]RGB_Sig;

output HSYNC;
output VSYNC;



inout [7:0]DATA;

/************************************************/
reg [10:0]C1;
reg [9:0]C2;
reg rH,rV;
	 
	 always @ ( posedge CLK or negedge RSTn )
	     if( !RSTn )
		      begin
				     C1 <= 11'd0;
					 C2 <= 10'd0;
					 rH <= 1'b1;
					 rV <= 1'b1;
				end
		  else 
		      begin
				    
					 if( C1 == 1904 ) rH <= 1'b0; 
				     else if( C1 == 152  ) rH <= 1'b1;
				     //else if( C1 == 0 ) rH <= 1'b0;
					 
					 if( C2 == 932 ) rV <= 1'b0;
					 else if( C2 == 3  ) rV <= 1'b1;
					 //else if( C2 == 0 ) rV <= 1'b0;
					 
					 if( C2 == 932 ) C2 <= 10'd1;
					 else if( C1 == 1904 ) C2 <= C2 + 1'b1;
					 
				     if( C1 == 1904 ) C1 <= 11'd1;
					 else C1 <= C1 + 1'b1;
					 
				end
assign HSYNC = rH;
assign VSYNC = rV;
	 
	 /********************************/
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
		 else 
		   case(i)
			   0:
				if(H2L_Sig_V)begin  i<=1'b1;   end
				else
			   	begin
						  SRAM_WE_r<=1'd0;
						  SRAM_CE_r<=1'd0;
						  SRAM_OE_r<=1'd1;
						  SRAM_LB_r<=1'd0;
						  SRAM_UB_r<=1'd1;                   // data in
						  Done_VGA_R<=1'd1;
						  Done_Collect_R<=1'd0; 
						 
					end
	         1:
		   	if(H2L_Sig_V)begin   i<=1'b0;     end
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
		//		4:         begin  i<=4'd1;  end 
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
		 else if(VSYNC_Count==240 )
		       begin
						 VSYNC_Count<=9'd0;				
				 end
		 else if(HREF_Count==640 && Done_VGA_R)
			    begin
						 VSYNC_Count<=VSYNC_Count+1'b1;
			    end
		 else
		             VSYNC_Count<=VSYNC_Count;
		
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
                   HREF_Count<=10'd1;
			    end				
		  else if(L2H_Sig_H && L2H_Sig_P && Done_VGA_R)
				 begin
					HREF_Count<=HREF_Count+1'd1;
					ADDR_r<=ADDR_r+1'b1;
					Y_Data_r<=Y_Data;
				 end 
		  else if(Done_Collect_R==1)
		         ADDR_r<=18'b0;
/********************VGAÉ¨Ãè*********************************/
	 
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
					 if( (C1 > 152 + 232 + _XOFF && C1 <= 152 + 232 + _XOFF +_X) && 
					     (C2 > 3 + 28 + _YOFF && C2 <= 3 + 28 + _YOFF + _Y) && Done_Collect_R)
					     begin 
						      isRectangle <= 1'b1;
						      x <= C1 - _XOFF - 152 - 232 - 1; 
						      y <= C2 - _YOFF - 3 - 28 - 1;
					         ADDR_R = (y << 9 +  y <<7) + x ; //address = y*640+x
					     end
					 else 
					         isRectangle <= 1'b0;
		       end
/*****************************************************/

			
wire [7:0]DataOut;
assign DATA=Done_VGA_R ? Y_Data_r : 8'bzz;
assign DataOut=Done_Collect_R ? DATA : DataOut;
assign ADDR=Done_Collect_R ? ADDR_R : ADDR_r;
/*****************************************************/
reg [2:0]rRGB;
always @ (posedge CLK or negedge RSTn)
         if(!RSTn)
			       rRGB<=3'b000;
         else if(Done_Collect_R)
						begin			
							   if(DataOut<=8'b01111110)
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




