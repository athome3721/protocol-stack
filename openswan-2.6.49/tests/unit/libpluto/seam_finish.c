struct pluto_crypto_req;
void finish_dh_v2(struct state *st,
		  struct pluto_crypto_req *r)
{
	//struct pcr_skeycalc_v2 *dhv2 = &r->pcr_d.dhv2;

#define CLONEIT(X) \
    clonetochunk(st->st_##X \
		 , tc3_results_##X \
		 , sizeof(tc3_results_##X) \
		 ,   "calculated " #X "shared secret");

    CLONEIT(shared);
    CLONEIT(skey_d);
    CLONEIT(skey_ai);
    CLONEIT(skey_ar);
    CLONEIT(skey_ei);
    CLONEIT(skey_er);
    CLONEIT(skey_pi);
    CLONEIT(skey_pr);
#undef CLONEIT

    st->hidden_variables.st_skeyid_calculated = TRUE;
}
