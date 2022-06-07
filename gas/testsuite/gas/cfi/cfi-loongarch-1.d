#readelf: -wf
#name: CFI on LOONGARCH

Contents of the .eh_frame section:


00000000 0+0010 0+00 CIE
  Version:               1
  Augmentation:          "zR"
  Code alignment factor: 1
  Data alignment factor: -4
  Return address column: 1
  Augmentation data:     0c
  DW_CFA_def_cfa_register: r3
  DW_CFA_nop

00000014 0+0028 0+0018 FDE cie=0+00 pc=0+00..0+0020
  DW_CFA_advance_loc: 4 to 0+004
  DW_CFA_offset: r11 at cfa\+0
  DW_CFA_def_cfa_offset: 16
  DW_CFA_advance_loc: 4 to 0+008
  DW_CFA_offset: r22 at cfa-8
  DW_CFA_advance_loc: 4 to 0+00c
  DW_CFA_def_cfa: r22 ofs 0
  DW_CFA_advance_loc: 12 to 0+0018
  DW_CFA_restore: r22
  DW_CFA_advance_loc: 4 to 0+001c
  DW_CFA_def_cfa_register: r3
  DW_CFA_nop
  DW_CFA_nop

