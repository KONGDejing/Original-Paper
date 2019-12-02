module VGA_module
(
    input CLK,     //150M
	 input RSTn,
 
	 output HSYNC,
    output VSYNC,
	 output [2:0]RGB_Sig
);
/******************count计数*******************/

reg [22:0]count;
always @(posedge CLK or negedge RSTn)
  if(!RSTn)
     begin count<=23'd0; end
  else
	   count<=count+1'b1;
/*******************VGA同步****************************/

reg [9:0]C1;
reg [9:0]C2;
reg rH,rV; 
	 always @ ( posedge CLK or negedge RSTn )
	     if( !RSTn )
		      begin
				    C1 <= 10'd0;
					 C2 <= 10'd0;
					 rH <= 1'b1;
					 rV <= 1'b1;
					
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
					 else if(count%5==0)C1 <= C1 + 1'b1;				 
					 
				end
assign HSYNC = rH;
assign VSYNC = rV;

/********************VGA扫描*********************************/
	 
	 parameter _X = 10'd640, _Y = 10'd240, _XOFF = 10'd0, _YOFF = 10'd0; 
	 
/**************************************/
    reg isRectangle;
    reg [17:0]x,y;
	 reg [17:0]ADDR_R;
    reg [4:0]j;
	 reg [2:0]rRGB;

    always @ ( posedge CLK or negedge RSTn )
	     if( !RSTn )
		      begin
				    x <= 18'd0;
					 y <= 18'd0;
				    ADDR_R<=18'd0;
					 j<=5'd0;
	             rRGB<=3'd0;				 
				end
			else
			case(j)
				0:
			   begin				
				    // step 1 : compute data address and index-n
					 if( (C1 > 96 + 48 + _XOFF && C1 <= 96 + 48 + _XOFF +_X) && 
					     (C2 > 2 + 33 + _YOFF && C2 <= 2 + 33 + _YOFF + _Y) )
					     begin 							 
								isRectangle <= 1'b1;
								x <= C1 - _XOFF - 96 - 48 - 1; 
								y <= C2 - _YOFF - 2 - 33 - 1;	
		                  j<=j+1'b1;rRGB<=3'b111;							
						  end				 
					 else                       
					    begin isRectangle <= 1'b0;  j<=j+1'b1; rRGB<=3'b000;	end 
		       end
				 1:begin j<=j+1'b1; ADDR_R <= (y << 9 +  y <<7) + x;end   //address = y*640+x
             2,3:begin j<=j+1'b1; end				 
				 4:begin   j<=1'b0; end
			endcase
/**************************************************************************/
			
assign RGB_Sig=rRGB;			
			
			
			
			
endmodule 