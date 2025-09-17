#include <bits/stdc++.h>
#define fi first
#define se second
#define rep(i,n) for(int i = 0; i < (n); ++i)
#define rrep(i,n) for(int i = 1; i <= (n); ++i)
#define drep(i,n) for(int i = (n)-1; i >= 0; --i)
#define srep(i,s,t) for (int i = s; i < t; ++i)
#define rng(a) a.begin(),a.end()
#define maxs(x,y) (x = max(x,y))
#define mins(x,y) (x = min(x,y))
#define limit(x,l,r) max(l,min(x,r))
#define lims(x,l,r) (x = max(l,min(x,r)))
#define isin(x,l,r) ((l) <= (x) && (x) < (r))
#define pb push_back
#define sz(x) (int)(x).size()
#define pcnt __builtin_popcountll
#define uni(x) x.erase(unique(rng(x)),x.end())
#define snuke srand((unsigned)clock()+(unsigned)time(NULL));
#define show(x) cout<<#x<<" = "<<x<<endl;
#define PQ(T) priority_queue<T,v(T),greater<T> >
#define bn(x) ((1<<x)-1)
#define dup(x,y) (((x)+(y)-1)/(y))
#define newline puts("")
#define v(T) vector<T>
#define vv(T) v(v(T))
using namespace std;
typedef long long int ll;
typedef unsigned uint;
typedef unsigned long long ull;
typedef pair<int,int> P;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ll> vl;
typedef vector<P> vp;
inline int in() { int x; scanf("%d",&x); return x;}
template<typename T>inline istream& operator>>(istream&i,v(T)&v)
{rep(j,sz(v))i>>v[j];return i;}
template<typename T>string join(const v(T)&v)
{stringstream s;rep(i,sz(v))s<<' '<<v[i];return s.str().substr(1);}
template<typename T>inline ostream& operator<<(ostream&o,const v(T)&v)
{if(sz(v))o<<join(v);return o;}
template<typename T1,typename T2>inline istream& operator>>(istream&i,pair<T1,T2>&v)
{return i>>v.fi>>v.se;}
template<typename T1,typename T2>inline ostream& operator<<(ostream&o,const pair<T1,T2>&v)
{return o<<v.fi<<","<<v.se;}
template<typename T>inline ll suma(const v(T)& a) { ll res(0); for (auto&& x : a) res += x; return res;}
const double eps = 1e-10;
const ll LINF = 1001002003004005006ll;
const int INF = 1001001001;
#define dame { puts("-1"); return 0;}
#define yn {puts("YES");}else{puts("NO");}
const int MX = 200005;
typedef v(vp) vvp;

// Segment tree with lazy prop
struct F { // min func
  typedef ll TF;
  TF d;
  F(TF d=0):d(d) {}
  F& operator+=(const F& f) {
    maxs(d, f.d);
    return *this;
  }
  F operator+(const F& f) const { return F(*this) += f;}
};
struct G { // lazy add func
  typedef ll TG;
  TG d;
  G(TG d=0):d(d) {}
  void operator()(F& f) const {
    f.d += d;
  }
  void operator*=(const G& g) {
    d += g.d;
  }
};
struct seg {
  struct FG {
    F f; G g;
    void apply(const G& _g) {
      _g(f);
      g *= _g;
    }
  };
  vector<FG> d; int n;
  seg(){}
  seg(int mx) {
    n = 1; while (n < mx) n <<= 1;
    d = vector<FG>(n<<1);
  }
  int width(int i) { return 1<<(__builtin_clz(i)-__builtin_clz(n));}
  void upd(int i) { d[i].f = d[i<<1].f+d[i<<1|1].f;}
  FG& operator[](int i) { return d[n+i];}
  void init() { drep(i,n) upd(i);}
  void prop(int i) {
    d[i<<1].apply(d[i].g);
    d[i<<1|1].apply(d[i].g);
    d[i].g = G();
  }
  void add(int l, int r, G g) { add(l,r,g,1,0,n);}
  void add(int a, int b, const G& g, int i, int l, int r) {
    if (a <= l && r <= b) {
      d[i].apply(g);
      return;
    }
    prop(i);
    int c = (l+r)>>1;
    if (a < c) add(a,b,g,i<<1,l,c);
    if (c < b) add(a,b,g,i<<1|1,c,r);
    upd(i);
  }
  F get(int l, int r) { return get(l,r,1,0,n);}
  F get(int a, int b, int i, int l, int r) {
    if (a <= l && r <= b) return d[i].f;
    prop(i);
    int c = (l+r)>>1;
    F res;
    if (a < c) res += get(a,b,i<<1,l,c);
    if (c < b) res += get(a,b,i<<1|1,c,r);
    return res;
  }
};
//


int main() {
  int n,m;
  scanf("%d%d",&n,&m);
  vvp ps(n);
  rep(i,m) {
    int l,r,a;
    scanf("%d%d%d",&l,&r,&a);
    --l; --r;
    ps[r].pb(P(l,a));
  }
  seg t(n+2);
  rep(i,n) {
    ll now = 0;
    if (i) now = t.get(0,i).d;
    t.add(i,i+1,now);
    for (P p : ps[i]) {
      int l = p.fi, a = p.se;
      t.add(l,i+1,a);
    }
  }
  ll ans = t.get(0,n).d;
  cout<<ans<<endl;
  return 0;
}




















