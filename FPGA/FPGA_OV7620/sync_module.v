	module sync_module
(
    CLK, RSTn,
	 VSYNC_Sig, HSYNC_Sig, Ready_Sig,
	 Column_Addr_Sig, Row_Addr_Sig
);

    input CLK;
	 input RSTn;
	 output VSYNC_Sig;
	 output HSYNC_Sig;
	 output Ready_Sig;
	 output [10:0]Column_Addr_Sig;
	 output [10:0]Row_Addr_Sig;
	 
	 /********************************/
	 
	 reg [10:0]Count_H;

	 always @ ( posedge CLK or negedge RSTn )
	     if( !RSTn )
				 Count_H <= 11'd0;
			else if( Count_H == 11'd1904)
			    Count_H <= 11'd0;
			else 
			    Count_H <= Count_H + 1'b1;
    
	 /********************************/
	 
	 reg [10:0]Count_V;
		 
	 always @ ( posedge CLK or negedge RSTn )
	     if( !RSTn )
		      Count_V <= 11'd0;
		  else if( Count_V == 11'd932 )
		      Count_V <= 11'd0;
		  else if( Count_H == 11'd1904 )
		      Count_V <= Count_V + 1'b1;
	
	 /********************************/
	 
	 reg isReady;
	 
	 always @ ( posedge CLK or negedge RSTn )
	     if( !RSTn )
		      isReady <= 1'b0;
        else if( ( Count_H > 11'd384 && Count_H < 11'd1824 ) && 
			        ( Count_V > 11'd31 && Count_V < 11'd931 ) )
		      isReady <= 1'b1;
		  else
		      isReady <= 1'b0;
		    
	 /*********************************/
	 
	 assign VSYNC_Sig = ( Count_V <= 11'd3 ) ? 1'b0 : 1'b1;
	 assign HSYNC_Sig = ( Count_H <= 11'd152 ) ? 1'b0 : 1'b1;
	 assign Ready_Sig = isReady; 
	                       
	 
	 /********************************/
	 
	 assign Column_Addr_Sig = isReady ? Count_H - 11'd385 : 11'd0;    // Count from 0;
	 assign Row_Addr_Sig = isReady ? Count_V - 11'd32 : 11'd0; // Count from 0;
	
	 /********************************/
	 
endmodule
