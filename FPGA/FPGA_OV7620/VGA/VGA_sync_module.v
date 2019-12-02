module VGA_sync_module 
(
     input CLK,
	 input RSTn,
	 output HSYNC,
	 output VSYNC,
	 output [10:0]qC1,
	 output [9:0]qC2
);

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
				
    /********************************/
    
	 assign qC1 = C1;
	 assign qC2 = C2;
	 
	 assign HSYNC = rH;
	 assign VSYNC = rV;
	 
	 /********************************/


endmodule
