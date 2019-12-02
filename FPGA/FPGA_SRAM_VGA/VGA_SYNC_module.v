/*******************VGAÍ¬²½****************************/
module VGA_SYNC_module
(
   input CLK,      //25M
	input RSTn,
   output qc1,
	output qc2,
	output VSYNC,
	output HSYNC


);
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
					 else C1 <= C1 + 1'b1;
					 
					 sram_ce_r<=1'b0;
					 
				end
assign HSYNC = rH;
assign VSYNC = rV;
assign qc1=C1;
assign qc2=C2;



endmodule 