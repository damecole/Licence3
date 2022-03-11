ghdl -a tb_processeur.vhd 
ghdl -a datapath2.vhd
ghdl -a processeur.vhd
ghdl -a --ieee=synopsys control_unit.vhd 
#ghdl -e datapath 
#ghdl -r tb_datapath --stop-time=500ns --wave=tb_datapath.ghw
#gtkwave tb_datapath.ghw