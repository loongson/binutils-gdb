/* Test insn relocs.  */
.text
nop

/* Jump Insns.  */
/* b16.  */
beq  $r4,$r5,%b16(.L1)
bne  $r4,$r5,%b16(.L1)
blt  $r4,$r5,%b16(.L1)
bge  $r4,$r5,%b16(.L1)
bltu $r4,$r5,%b16(.L1)
bgeu $r4,$r5,%b16(.L1)
jirl $r4,$r5,%b16(.L1)

/* b21.  */
beqz $r4,%b21(.L1)
bnez $r4,%b21(.L1)

/* b26.  */
b  %b26(.L1)
bl %b26(.L1)


/* ABS Insns.  */
/* lu12i.w.  */
lu12i.w $r4,%l_hi20_pa(.L1)

/* addi.w/d ld.b/h/w/d.  */
addi.w $r5,$r4,%l_lo12_pa(.L1)
addi.d $r5,$r4,%l_lo12_pa(.L1)
ld.b $r5,$r4,%l_lo12_pa(.L1)
ld.h $r5,$r4,%l_lo12_pa(.L1)
ld.w $r5,$r4,%l_lo12_pa(.L1)
ld.d $r5,$r4,%l_lo12_pa(.L1)

/* lu32i.d.  */
lu32i.d $r4,%h_lo20(.L1)

/* lu52i.d.  */
lu52i.d $r5,$r4,%h_hi12(.L1)


/* Pcala Insns.  */
/* pcalau12i.  */
pcalau12i $r4,%pcala_hi20_pa(.L1)
pcalau12i $r4,%got32_hi20_pa(.L1)
/* pa lo12 reused abs lo12.  */

/* addi.w/d ld.b/h/w/d.  */
addi.w $r5,$r4,%got_lo12_pa(.L1)
addi.d $r5,$r4,%got_lo12_pa(.L1)
ld.b $r5,$r4,%got_lo12_pa(.L1)
ld.h $r5,$r4,%got_lo12_pa(.L1)
ld.w $r5,$r4,%got_lo12_pa(.L1)
ld.d $r5,$r4,%got_lo12_pa(.L1)


/* GOT64 Insns.  */
/* lu12i.w.  */
lu12i.w $r4,%got64_l_hi20_pa(.L1)

/* lu32i.d.  */
lu32i.d $r4,%got64_h_lo20(.L1)

/* lu52i.d.  */
lu52i.d $r5,$r4,%got64_h_hi12(.L1)


/* Jump Insns with addend.  */
/* b16.  */
beq  $r4,$r5,%b16(.L1 + 0x8)
bne  $r4,$r5,%b16(.L1 + 0x8)
blt  $r4,$r5,%b16(.L1 + 0x8)
bge  $r4,$r5,%b16(.L1 + 0x8)
bltu $r4,$r5,%b16(.L1 + 0x8)
bgeu $r4,$r5,%b16(.L1 + 0x8)
jirl $r4,$r5,%b16(.L1 + 0x8)

/* b21.  */
beqz $r4,%b21(.L1 + 0x8)
bnez $r4,%b21(.L1 + 0x8)

/* b26.  */
b  %b26(.L1 + 0x8)
bl %b26(.L1 + 0x8)


/* ABS Insns.  */
/* lu12i.w.  */
lu12i.w $r4,%l_hi20_pa(.L1 + 0x8)

/* addi.w/d ld.b/h/w/d.  */
addi.w $r5,$r4,%l_lo12_pa(.L1 + 0x8)
addi.d $r5,$r4,%l_lo12_pa(.L1 + 0x8)
ld.b $r5,$r4,%l_lo12_pa(.L1 + 0x8)
ld.h $r5,$r4,%l_lo12_pa(.L1 + 0x8)
ld.w $r5,$r4,%l_lo12_pa(.L1 + 0x8)
ld.d $r5,$r4,%l_lo12_pa(.L1 + 0x8)

/* lu32i.d.  */
lu32i.d $r4,%h_lo20(.L1 + 0x8)

/* lu52i.d.  */
lu52i.d $r5,$r4,%h_hi12(.L1 + 0x8)


/* Pcala Insns.  */
/* pcalau12i.  */
pcalau12i $r4,%pcala_hi20_pa(.L1 + 0x8)
pcalau12i $r4,%got32_hi20_pa(.L1 + 0x8)
/* pa lo12 reused abs lo12.  */

/* addi.w/d ld.b/h/w/d.  */
addi.w $r5,$r4,%got_lo12_pa(.L1 + 0x8)
addi.d $r5,$r4,%got_lo12_pa(.L1 + 0x8)
ld.b $r5,$r4,%got_lo12_pa(.L1 + 0x8)
ld.h $r5,$r4,%got_lo12_pa(.L1 + 0x8)
ld.w $r5,$r4,%got_lo12_pa(.L1 + 0x8)
ld.d $r5,$r4,%got_lo12_pa(.L1 + 0x8)


/* GOT64 Insns.  */
/* lu12i.w.  */
lu12i.w $r4,%got64_l_hi20_pa(.L1 + 0x8)

/* lu32i.d.  */
lu32i.d $r4,%got64_h_lo20(.L1 + 0x8)

/* lu52i.d.  */
lu52i.d $r5,$r4,%got64_h_hi12(.L1 + 0x8)






