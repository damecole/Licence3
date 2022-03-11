-- Unite de controle processeur pipeline
-- V1
-- Auteur : GIEULES Damien
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;

entity control_unit is
port (	Clk 		: in std_logic;

	Inst 		: in std_logic_vector(31 downto 0);
	Src_PC 		: out std_logic;

	Src1, Src2	: out std_logic_vector(3 downto 0);

	Imm     	: out std_logic_vector(15 downto 0);
	Src_Op_B 	: out std_logic; 	
	Cmd_UAL 	: out std_logic_vector(1 downto 0);
	Z,N		: in std_logic;
	
	Src_Adr_Branch 	: out std_logic; 	
	RW, Bus_Val 	: out std_logic;

	Banc_Src 	: out std_logic_vector(1 downto 0);
	Dest 		: out std_logic_vector(3 downto 0);
	Banc_Ecr 	: out std_logic 
);
end control_unit;

architecture beh of control_unit is

signal di_ri, di_Bus_Donnees_in :  std_logic_vector(31 downto 0) := "00000000000000000000000000000000";
signal di_src_PC, ex_src_pc, mem_src_pc, di_Banc_Ecr, di_Src_Op_B, di_Src_Adr_Branch : std_logic := '1';
signal di_Cmd_ual, di_Banc_Src :  std_logic_vector(1 downto 0);
signal codeop_di, reg_src1_di, reg_src2_di,reg_dest_di :  std_logic_vector(3 downto 0) := "0000";
signal imm_di :  std_logic_vector(15 downto 0);
	

signal di_ex, ex_Bus_Donnees_in :  std_logic_vector(31 downto 0) := "00000000000000000000000000000000";
signal ex_Banc_Ecr, ex_Src_Op_B, ex_Src_Adr_Branch : std_logic := '1';
signal ex_Cmd_ual, ex_Banc_Src :  std_logic_vector(1 downto 0);
signal codeop_ex, reg_src1_ex, reg_src2_ex, reg_dest_ex :  std_logic_vector(3 downto 0) := "0000";
signal imm_ex :  std_logic_vector(15 downto 0);

signal di_mem, mem_Bus_Donnees_in :  std_logic_vector(31 downto 0) := "00000000000000000000000000000000";
signal mem_Banc_Ecr, mem_Src_Op_B, mem_Src_Adr_Branch : std_logic := '1';
signal mem_Cmd_ual, mem_Banc_Src :  std_logic_vector(1 downto 0);
signal codeop_mem, reg_src1_mem, reg_src2_mem, reg_dest_mem :  std_logic_vector(3 downto 0) := "0000";
signal imm_mem :  std_logic_vector(15 downto 0);


begin

	-- registre RI
	ri : process(clk)
	begin
		if Clk'event and Clk='0' then
			di_ri <= Inst;
		end if;
	end process;

	-- decodeur \ ETAPE DI
	---------------------
	-- a vous
	---------------------
	codeop_di <= di_ri (31 downto 28);
	reg_src1_di <= di_ri (27 downto 24);
	reg_src2_di <= di_ri (23 downto 20);
	reg_dest_di <= di_ri (19 downto 16);
	imm_di <= di_ri (15 downto 0);

	decodeur_di : process(codeop_di)
	begin
		case codeop_di is 
			when "0000" => --NOP
				
					
			when "0001" => --ADDI
						di_src_PC <= '1'; 
						di_Banc_Src 	<= "01";
						di_Banc_Ecr	<= '1';
						di_Cmd_ual         <= "00";     -- Z=0, N=0;
						di_Src_Op_B        <= '0';
						di_Src_Adr_Branch  <= '-';
						di_Bus_Donnees_in  <= "UUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUU";
			
			when "0010" => --SUB
						di_src_PC 		<= '1';
						di_Banc_Src 	<= "01";
						di_Banc_Ecr	<= '1';
						di_Cmd_ual         <= "01";     -- Z=0, N=0;
						di_Src_Op_B        <= '0';
						di_Src_Adr_Branch  <= '-';
						di_Bus_Donnees_in  <= "UUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUU";

			when "0011" => --SW
						di_src_PC 		<= '1';
						di_Banc_Src 	<= "00";
						di_Banc_Ecr	<= '0';
						di_Cmd_ual         <= "00";     -- Z=0, N=0;
						di_Src_Op_B        <= '0';
						di_Src_Adr_Branch  <= '-';
						di_Bus_Donnees_in  <= "UUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUU";
				
			when "0101" => --JSR
						di_src_PC 		<= '0';
						di_Banc_Src 	<= "10";
						di_Banc_Ecr	<= '1';
						di_Cmd_ual         <= "10";     -- Z=0, N=0;
						di_Src_Op_B        <= '0';
						di_Src_Adr_Branch  <= '1';
						di_Bus_Donnees_in  <= "UUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUU";

			when "0110" => --RTS
			when "0111" => --BEQ
						reg_src1_di 		<= "0100";	--R4
						reg_src2_di 		<= "0010"; --R2
						if reg_src2_di = reg_src1_di then
							di_src_PC 		<= '0';
							di_Banc_Src 	<= "10";
							di_Banc_Ecr	<= '0';
							di_Cmd_ual         <= "10";     -- Z=0, N=0;
							di_Src_Op_B        <= '0';
							di_Src_Adr_Branch  <= '1';
							di_Bus_Donnees_in  <= "UUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUU";
						end if;
			when "1000" => 
			when others => 
		end case;
	end process;		


	-- registre pour gerer le pipeline
	ex : process(clk)
	begin
		if Clk'event and Clk='0' then
			ex_Cmd_ual <= di_Cmd_ual;
			--ex_src_PC 		<= di_src_PC;
			--ex_Banc_Src 	<= di_Banc_Src;
			--ex_Banc_Ecr	<= di_Banc_Ecr;
			ex_Cmd_ual         <= di_Cmd_ual;     
			ex_Src_Op_B        <= di_Src_Op_B;
			---ex_Src_Adr_Branch  <= di_Src_Adr_Branch;
			--ex_Bus_Donnees_in  <= di_Bus_Donnees_in;
		end if;
	end process;

	mem : process(clk)
	begin
		if Clk'event and Clk='0' then
			--mem_Cmd_ual 			<= ex_Cmd_ual;
			--mem_src_PC 			<= ex_src_PC;
			--mem_Banc_Src 		<= ex_Banc_Src;
			--mem_Banc_Ecr			<= ex_Banc_Ecr;   
			--mem_Src_Op_B         <= ex_Src_Op_B;
			--mem_Src_Adr_Branch   <= ex_Src_Adr_Branch;
			mem_Bus_Donnees_in   <= ex_Bus_Donnees_in;
		end if;
	end process;
				

	-- registres pipeline
	---------------------
	-- a vous
	---------------------


end beh;
