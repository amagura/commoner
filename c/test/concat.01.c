#ifndef COMMON_CONCAT_01_C_GUARD
# define COMMON_CONCAT_01_C_GUARD 1
# if !defined(concat_00_IDX)
int main()
{
# endif
     s = malloc(sz*(sizeof(*s)));
     s0 = malloc(sz0*(sizeof(*s0)));
     strterm(s, sz);
     strterm(s0, sz0);
     getentropy(s0, sz0);
# if concat_00_IDX == 0
     r = catm(s, sz, s0);
# elif concat_00_IDX == 1
     r = catl(s, sz, s0);
//# elif concat_00_IDX == 2
//     r = cat(s, sz, s0);
# elif concat_00_IDX == 2
     r = concatm(s, sz, s0);
# elif concat_00_IDX == 3
     r = concatl(s, sz, s0);
# endif
     printf("r0: %lu\n", (ulong)r);
# if concat_00_IDX == 0
     r = catm(s, sz, s, s, s);
# elif concat_00_IDX == 1
     r = catl(s, sz, s, s, s);
//# elif concat_00_IDX == 2
//     r = cat(s, sz, s, s, s);
# elif concat_00_IDX == 2
     r = concatm(s, s, s, s);
# elif concat_00_IDX == 3
     r = concatl(s, sz, s, s, s);
# endif
     printf("r1: %lu\n", (ulong)r);
     r = 0;
     free(s);
     free(s0);
# if !defined(concat_00_IDX)
     return 0;
}
# endif
#endif
