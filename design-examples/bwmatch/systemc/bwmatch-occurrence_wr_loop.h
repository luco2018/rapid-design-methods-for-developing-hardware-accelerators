// See LICENSE for license details.
/*[[[cog
     import cog
     from cog_acctempl import *
     from dut_params import dut
     if "thread_nm" not in globals():
       lst = cog.previous.lstrip('/').rstrip('\n').split('=')
       assert( lst[0]=="thread_nm")
       assert( len(lst)==2)
       global thread_nm
       thread_nm = lst[1]
     cog.outl( "//thread_nm=" + thread_nm)
  ]]]*/
//thread_nm=occurrence_wr_loop
//[[[end]]] (checksum: 3b5a5f297e842b1693e64263dc9c36d0)
/*[[[cog
     c = dut.get_cthread(thread_nm)
     cog.outl("void %s() {" % (c.nm,))
     for p in c.ports:
       cog.outl("  %s;" % p.reset)
  ]]]*/
void occurrence_wr_loop() {
  clReqOut.reset_put();
  irowQ.reset_get();
//[[[end]]] (checksum: e5024222a0c8669c5b36c6bac0399aa0)

  /*[[[cog
       if c.writes_to_done:
         cog.outl("done = false;")
    ]]]*/
  //[[[end]]] (checksum: d41d8cd98f00b204e9800998ecf8427e)
  wait();
  while (1) {
    BWState inp = irowQ.get();

    unsigned int crow;

    if ( inp.state == 0)
      crow = inp.res.l >> 7;
    else
      crow = inp.res.u >> 7;

    if ( crow == config.read().m()) {
      --crow;
    }

    clReqOut.put( MemSingleReadReqType<BWCacheLine,BWState>( config.read().getClAddr( crow), inp));

    wait();
  }
}
