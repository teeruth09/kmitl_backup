.ALIASES
R_R5            R5(1=N01462 2=GND ) CN @PROJECT1.SCHEMATIC1(sch_1):I00749@ANALOG.R.Normal(chips)
V_V1            V1(+=N07899 -=GND ) CN @PROJECT1.SCHEMATIC1(sch_1):I00044@SOURCE.VDC.Normal(chips)
D_D2            D2(1=N01052 2=N07899 ) CN @PROJECT1.SCHEMATIC1(sch_1):I00526@EDIODE.1N4148.Normal(chips)
X_U1A           U1A(+=N01052 -=N02859 V+=N07899 V-=GND OUT=VOUT ) CN @PROJECT1.SCHEMATIC1(sch_1):I00800@OPAMP.LM358.Normal(chips)
D_D3            D3(1=VOUT 2=N01462 ) CN @PROJECT1.SCHEMATIC1(sch_1):I00584@EDIODE.1N4148.Normal(chips)
R_R7            R7(1=N02859 2=N07899 ) CN @PROJECT1.SCHEMATIC1(sch_1):I08333@ANALOG.R.Normal(chips)
D_D1            D1(1=N07899 2=N01025 ) CN @PROJECT1.SCHEMATIC1(sch_1):I00398@EDIODE.1N4148.Normal(chips)
R_R1            R1(1=GND 2=N01025 ) CN @PROJECT1.SCHEMATIC1(sch_1):I00653@ANALOG.R.Normal(chips)
R_R2            R2(1=GND 2=N01052 ) CN @PROJECT1.SCHEMATIC1(sch_1):I00677@ANALOG.R.Normal(chips)
R_R4            R4(1=N02859 2=GND ) CN @PROJECT1.SCHEMATIC1(sch_1):I00701@ANALOG.R.Normal(chips)
_    _(Vout=VOUT)
_    _(GND=GND)
.ENDALIASES
