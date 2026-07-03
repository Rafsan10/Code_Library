#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T> using o_set = tree<T, null_type, 
less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T> using o_multiset = tree<pair<T, int>, null_type, 
less<pair<T, int>>, rb_tree_tag, tree_order_statistics_node_update>;
/* 
o_set<int> st;
*st.find_by_order(0); // 0-th element
o_multiset<int> mst;
int timer = 0; // use a global/local timer for unique IDs
mst.insert({5, timer++});
mst.erase(mst.lower_bound({5, 0})); // Erases exactly ONE instance of 5
mst.order_of_key({5, 0}); // strictly less than 5
*/

// Faster hash
gp_hash_table<int, int> mp;
// Or
unordered_map<int, int> mp;
mp.reserve(n * 2);
mp.max_load_factor(0.7);