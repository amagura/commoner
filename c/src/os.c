inline size_t cntlns(FILE *FP)
{
        size_t r = 0;
        while ((EOF != (fscanf(fp, "%*[^\n]"), fscanf(fp, "%*c")))
                ++r;
        return r;
}
