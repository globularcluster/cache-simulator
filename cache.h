#ifndef CACHE_H
#define CACHE_H


class Cache
{
private:
  int   *Val,
        *Tag,
        *Dirty;

  int   n_sets,
        b_size,
        assoc;

  int   nbits_offset,
        nbits_indice,
        nbits_tag,

        access,
        hits,
        miss;

public:
  Cache();
  Cache(int, int, int);
  ~Cache();

  void alocaCache();
  void setVal(int conj, int assoc, int val);
  void setTag(int conj, int assoc, int val);
  int getVal(int conj, int assoc);
  int getTag(int conj, int assoc);
  int getAssoc() { return assoc; }
  int getNsets() { return n_sets; }
  int getHits() { return hits; }
  int getMiss() { return miss; }
  int cache_access(int, int);

};



#endif //MACHINE_H
