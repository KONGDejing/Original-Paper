module bypass_module
(
     input CLK,
	  input RSTn,
     input UHSYNC,
	  input UVSYNC,
	  output HSYNC,
	  output VSYNC
	  

);


 reg [1:0]rBy1,rBy2,rBy3,rBy4;
	 
	 always @ ( posedge CLK or negedge RSTn )
	     if( !RSTn )
		      begin
				     rBy1 <= 2'b11;
					 rBy2 <= 2'b11;
					 rBy3 <= 2'b11;
					 rBy4 <= 2'b11;
				end
		  else 
		      begin
				     rBy1 <= { UHSYNC, UVSYNC };
					 rBy2 <= rBy1;
					 rBy3 <= rBy2;
					 rBy4 <= rBy3;
				end
				
	/***************************/
	
	assign { HSYNC, VSYNC } = rBy4; 
	
	/***************************/

endmodule
