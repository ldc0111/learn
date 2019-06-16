## 宏替换

### 棋子的计算

```c
//棋子的计算
#define coord_xy(board, x, y) ((x) + (y) * board_size(board))
//他提前的讲xy放入了c的第0和第一个位置
#define coord_x(c, b) (board_statics.coord[c][0])
#define coord_y(c, b) (board_statics.coord[c][1])
/* TODO: Smarter way to do this? */
#define coord_dx(c1, c2, b) (coord_x(c1, b) - coord_x(c2, b))
#define coord_dy(c1, c2, b) (coord_y(c1, b) - coord_y(c2, b))

```

### 旗子的选择

```c

#define uctd_try_node_children(tree, descent, allow_pass, parity, tenuki_d, di, urgency) \
	/* Information abound best children. 信息丰富，最好的孩子*/ \
	/* XXX: We assume board <=25x25.我们假设电路板<=25x25 */ \
	struct uct_descent dbest[BOARD_MAX_MOVES + 1] = { { .node = descent->node->children, .lnode = NULL } }; int dbests = 1; \
	floating_t best_urgency = -9999; \
	/* Descent children iterator. */ \
	struct uct_descent dci = { .node = descent->node->children, .lnode = descent->lnode ? descent->lnode->children : NULL }; \
	\
	for (; dci.node; dci.node = dci.node->sibling) { \
		floating_t urgency; \
		/* Do not consider passing early. */ \
		if (unlikely((!allow_pass && is_pass(node_coord(dci.node))) || (dci.node->hints & TREE_HINT_INVALID))) \
			continue; \
		/* Position dci.lnode to point at or right after the local
		 * node corresponding to dci.node. */ \
		while (dci.lnode && node_coord(dci.lnode) < node_coord(dci.node)) \
			dci.lnode = dci.lnode->sibling; \
		/* Set up descent-further iterator. This is the public-accessible
		 * one, and usually is similar to dci. However, in case of local
		 * trees, we may keep next-candidate pointer in dci while storing
		 * actual-specimen in di. */ \
		struct uct_descent di = dci; \
		if (dci.lnode) { \
			/* Set lnode to local tree node corresponding
			 * to node (dci.lnode, pass-lnode or NULL). */ \
			di.lnode = tree_lnode_for_node(tree, dci.node, dci.lnode, tenuki_d); \
		}

		/* ...your urgency computation code goes here... */

```





## 结构体

### engine_id

```c++
enum engine_id {
	E_RANDOM,
	E_REPLAY,
	E_PATTERNSCAN,
	E_PATTERNPLAY,
	E_MONTECARLO, //蒙特卡洛树搜索
	E_UCT,//ucb问题，多臂老虎机问题，得知某个把手，被游戏的次数越少，玩他的概率越高，她赢得概率越高，他被玩的概率越高
	E_DISTRIBUTED, //分布式计算
	E_JOSEKI,//不经常用
#ifdef DCNN
	E_DCNN,//神经网络，用的也是蒙特卡洛树算发，加入了深度神经卷积网络
#endif
	E_MAX,//表示引擎的个数，编号从0开始，ifdef 作用的是还有代码裁剪
};
```

### engine_init_t 结构体数组

```c
//函数指针数组，下面的都是函数 作用是初始化不同的引擎
//typedef struct engine *(*engine_init_t)(char *arg, struct board *b);
static engine_init_t engine_init[E_MAX] = {
	engine_random_init,
	engine_replay_init,
	engine_patternscan_init,
	engine_patternplay_init,
	engine_montecarlo_init,
	engine_uct_init,
	engine_distributed_init,
	engine_joseki_init,
#ifdef DCNN
	engine_dcnn_init,
#endif
};
```

>  观看完这两个结构体请观看init_engine函数

### engine结构体

```c++
/* This is engine data structure. A new engine instance is spawned
 * for each new game during the program lifetime. */
/*这是引擎数据结构。生成新的引擎实例在程序生命周期内的每一个新游戏。*/
struct engine {
	char *name;
	char *comment;

	/* If set, do not reset the engine state on clear_board. */
    /*如果已设置，请勿在清除板上重置发动机状态。*/
	bool keep_on_clear;

	engine_notify_t          notify;
	engine_board_print_t     board_print;
	engine_notify_play_t     notify_play;
	engine_chat_t            chat;
	engine_undo_t            undo;
	engine_result_t          result;

	/* Generate a move. If pass_all_alive is true, <pass> shall be generated only
	 * if all stones on the board can be considered alive, without regard to "dead"
	 * considered stones. */
    /*生成移动。如果pass-all-live为真，则仅应生成<pass>
如果董事会上所有的石头都被认为是活的，而不考虑“死的”
被认为是石头。*/
	engine_genmove_t         genmove;

	/* Used by distributed engine */
    /*分布式引擎使用*/
	engine_genmoves_t        genmoves;

	/* List best moves for current position. */
    /*分布式引擎列表使用当前位置的最佳移动。*/
	engine_best_moves_t      best_moves;

	/* Evaluate feasibility of player @color playing at all free moves. Will
	 * simulate each move from b->f[i] for time @ti, then set
	 * 1-max(opponent_win_likelihood) in vals[i]. */
    /*评估玩家@color在所有自由移动中玩游戏的可行性。威尔
从b->f[i]模拟每次移动的时间@ti，然后在vals[i]中设置1-max（对手获胜概率）。*/*/
	engine_evaluate_t        evaluate;

	/* One dead group per queued move (coord_t is (ab)used as group_t). */
    /*每个排队移动一个死组（coord_t is（ab）用作组t）。*/
	engine_dead_group_list_t dead_group_list;

	/* Pause any background thinking being done, but do not tear down
	 * any data structures yet. */
    /*暂停正在进行的任何后台思考，但不要破坏任何数据结构。*/
	engine_stop_t            stop;

	/* e->data and e will be free()d by caller afterwards. */
    /*e->data和e随后将被调用方释放（）d。*/
	engine_done_t            done;

	/* Return current ownermap, if engine supports it. */
    /*如果引擎支持，返回当前所有者地图。*/
	engine_ownermap_t        ownermap;
	
	/* GoGui hook */
    /*GoGui钩*/
	engine_livegfx_hook_t   livegfx_hook;
	
	void *data;
};
```

### uct结构体

```c

/* Internal engine state. */
/*引擎内部状态*/
struct uct {
	int debug_level;
	enum uct_reporting {
		UR_TEXT,
		UR_JSON,
		UR_JSON_BIG,
	} reporting;
	int reportfreq;

	int games, gamelen;
	floating_t resign_threshold, sure_win_threshold;
	double best2_ratio, bestr_ratio;
	floating_t max_maintime_ratio;
	bool pass_all_alive; /* Current value，当前值 */
	bool allow_losing_pass;
	bool territory_scoring;
	int expand_p;
	bool playout_amaf;
	bool amaf_prior;
	int playout_amaf_cutoff;
	double dumpthres;
	int force_seed;
	bool no_tbook;
	bool fast_alloc;
	size_t max_tree_size;
	size_t max_pruned_size;
	size_t pruning_threshold;
	int mercymin;
	int significant_threshold;

	int threads;
	enum uct_thread_model {
		TM_TREE, /* Tree parallelization w/o virtual loss. 无虚拟损失的树并行化。*/
		TM_TREEVL, /* Tree parallelization with virtual loss. 树与虚损失并行化。*/
	} thread_model;
	int virtual_loss;
	bool pondering_opt; /* User wants pondering 用户想要思考 */
	bool pondering; /* Actually pondering now 正在思考*/
	bool slave; /* Act as slave in distributed engine. 在分布式引擎中充当从机*/
	int max_slaves; /* Optional, -1 if not set 可选，如果未设置-1*/
	int slave_index; /* 0..max_slaves-1, or -1 if not set 0..max_slaves-1或-1（如果未设置）*/
	enum stone my_color;

	int fuseki_end;
	int yose_start;

	int dynkomi_mask;
	int dynkomi_interval;
	struct uct_dynkomi *dynkomi;
	floating_t initial_extra_komi;

	floating_t val_scale;
	int val_points;
	bool val_extra;
	bool val_byavg;
	bool val_bytemp;
	floating_t val_bytemp_min;

	int random_policy_chance;
	bool local_tree;
	int tenuki_d;
	floating_t local_tree_aging;
#define LTREE_PLAYOUTS_MULTIPLIER 100
	floating_t local_tree_depth_decay;
	bool local_tree_allseq;
	bool local_tree_neival;
	enum {
		LTE_ROOT,
		LTE_EACH,
		LTE_TOTAL,
	} local_tree_eval;
	bool local_tree_rootchoose;

	struct {
		int level;
		int playouts;
	} debug_after;

	char *banner;

	struct uct_policy *policy;
	struct uct_policy *random_policy;
	struct playout_policy *playout;
	struct uct_prior *prior;
	struct uct_pluginset *plugins;
	struct joseki_dict *jdict;

	struct pattern_setup pat;
	/* Various modules (prior, policy, ...) set this if they want pattern
	 * database to be loaded. */
    /*各种模块（prior，policy，…）如果想要模式，就设置这个。
要加载的数据库。*/
	bool want_pat;

	/* Used within frame of single genmove. */
    /*在单个genmove的框架内使用*/
	struct board_ownermap ownermap;
	/* Used for coordination among slaves of the distributed engine. */
    /*用于分布式引擎的从机之间的协调。*/
	int stats_hbits;
	int shared_nodes;
	int shared_levels;
	double stats_delay; /* stored in seconds 以秒为单位存储*/
	int played_own;
	int played_all; /* games played by all slaves 所有奴隶玩的游戏*/

	/* Saved dead groups, for final_status_list dead */
    /*所有奴隶玩的游戏*/
	struct move_queue dead_groups;
	int dead_groups_move;

	/* Game state - maintained by setup_state(), reset_state(). */
    /*游戏状态-由setup_state（）、reset_state（）维护*/
	struct tree *t;
};

```

### parse_code and next__tok

```c
//命令执行的状态
enum parse_code {
	P_OK,//0值代表成功
	P_NOREPLY,
	P_DONE_OK,
	P_DONE_ERROR,
	P_ENGINE_RESET, //引擎被重置
	P_UNKNOWN_COMMAND,//未知的命令
};

/*to_传入一个字符串类型 strcspn 后面的那些字符在那个位置上，to_指向命令头，next指向
 * 将前部分置位为一个单独的字符串，next后移，strspn是跳过那些非空字符的起始位置，就是找参数*/
#define next_tok(to_) \
	to_ = gtp->next; \
	gtp->next = gtp->next + strcspn(gtp->next, " \t\r\n"); \
	if (*gtp->next) { \
		*gtp->next = 0; gtp->next++; \
		gtp->next += strspn(gtp->next, " \t\r\n"); \
	}

```

### gtp_command_t 和定义

```c
typedef enum parse_code
(*gtp_func_t)(struct board *board, struct engine *engine, struct time_info *ti, gtp_t *gtp);

typedef struct
{
	char *cmd;//命令
	gtp_func_t f;//命令执行的函数
} gtp_command_t;

static gtp_command_t commands[];

static gtp_command_t commands[] =
{
	{ "protocol_version",       cmd_protocol_version },
	{ "name",                   cmd_name },
	{ "echo",                   cmd_echo },
	{ "version",                cmd_version },
	{ "list_commands",          cmd_list_commands },
	{ "known_command",          cmd_known_command },
	{ "quit",                   cmd_quit },
	{ "boardsize",              cmd_boardsize },
	{ "clear_board",            cmd_clear_board },
	{ "komi",                   cmd_komi },
	{ "play",                   cmd_play },
	{ "genmove",                cmd_genmove },
	{ "time_left",              cmd_time_left },
	{ "time_settings",          cmd_kgs_time_settings },
	{ "set_free_handicap",      cmd_set_free_handicap },
	{ "place_free_handicap",    cmd_fixed_handicap },
	{ "fixed_handicap",         cmd_fixed_handicap },
	{ "final_score",            cmd_final_score },
	{ "final_status_list",      cmd_final_status_list },
	{ "undo",                   cmd_undo },

	{ "kgs-game_over",          cmd_kgs_game_over },
	{ "kgs-rules",              cmd_kgs_rules },
	{ "kgs-genmove_cleanup",    cmd_genmove },
	{ "kgs-time_settings",      cmd_kgs_time_settings },
	{ "kgs-chat",               cmd_kgs_chat },

	{ "pachi-predict",          cmd_pachi_predict },
	{ "pachi-tunit",            cmd_pachi_tunit },
	{ "pachi-genmoves",         cmd_pachi_genmoves },
	{ "pachi-genmoves_cleanup", cmd_pachi_genmoves },
	{ "pachi-gentbook",         cmd_pachi_gentbook },
	{ "pachi-dumptbook",        cmd_pachi_dumptbook },
	{ "pachi-evaluate",         cmd_pachi_evaluate },
	{ "pachi-result",           cmd_pachi_result },

	/* Short aliases */
	{ "predict",                cmd_pachi_predict },
	{ "tunit",		    cmd_pachi_tunit },

	{ "gogui-analyze_commands", cmd_gogui_analyze_commands },
	{ "gogui-livegfx",          cmd_gogui_livegfx },
	{ "gogui-ownermap",         cmd_gogui_ownermap },
	{ "gogui-score_est",        cmd_gogui_score_est },
	{ "gogui-best_moves",       cmd_gogui_best_moves },
	{ "gogui-winrates",         cmd_gogui_winrates },
#ifdef DCNN
	{ "gogui-dcnn_best",        cmd_gogui_dcnn_best },
	{ "gogui-dcnn_colors",      cmd_gogui_dcnn_colors },
	{ "gogui-dcnn_rating",      cmd_gogui_dcnn_rating },
#endif /* DCNN */
	{ "gogui-color_palette",    cmd_gogui_color_palette },

	{ 0, 0 }
};

```





### stone

```c
//棋子，没有子，黑子，白字，
//为了计算方便，当我们要求棋盘大小是19*19的情况下，他会加一层小边
//就是21*21的，就是旗子边的位置
enum stone {
	S_NONE,
	S_BLACK,
	S_WHITE,
	S_OFFBOARD,
	S_MAX,
};
```



### struct uct_thread_ctx

````c
/* Search thread context */
/*搜索线程上下文*/
struct uct_thread_ctx {
	int tid; //线程id
	struct uct *u;//引擎中的数据，传入字引擎
	struct board *b;//棋盘大小
	enum stone color;//执子颜色
	struct tree *t;//蒙特卡洛树
	unsigned long seed;//随机种子
	int games;//总共玩了多少次//传出参数
	struct time_info *ti;//时间限制
};
````

### struct move

```c
//位置（一一映射） 和颜色x × size + y = coord 
//传输方便
struct move {
	coord_t coord;
	enum stone color;
}
```



### struct board

```c
/* You should treat this struct as read-only. Always call functions below if
 * you want to change it. */
/*您应该将此结构视为只读。如果要更改函数，请始终调用下面的函数。*/

struct board {
	int size; /* Including S_OFFBOARD margin - see below. 棋盘的边长*/
	int size2; /* size^2  开一个平方*/
	int bits2; /* ceiling(log2(size2))表示用多杀个2进制为可以表示棋盘 */
	int captures[S_MAX];
	floating_t komi;
	int handicap;
	enum go_ruleset rules;//规则
	char *fbookfile;//棋谱
	struct fbook *fbook;

	int moves;
	struct move last_move;//倒数第一步，倒数第二步
	struct move last_move2; /* second-to-last move */
FB_ONLY(struct move last_move3); /* just before last_move2, only set if last_move is pass */
FB_ONLY(struct move last_move4); /* just before last_move3, only set if last_move & last_move2 are pass */
	/* Whether we tried to add a hash twice; board_play*() can
	 * set this, but it will still carry out the move as well! */
FB_ONLY(bool superko_violation);

	/* The following two structures are goban maps and are indexed by
	 * coord.pos. The map is surrounded by a one-point margin from
	 * S_OFFBOARD stones in order to speed up some internal loops.
	 * Some of the foreach iterators below might include these points;
	 * you need to handle them yourselves, if you need to. */
    /*下面的两个结构是Goban映射，并由coord.pos索引。为了加速一些内部循环，该映射被来自s摼ofboard stone的一个点边缘包围。下面的一些foreach迭代器可能包括这些点；如果需要，您需要自己处理它们。*/

	/* Stones played on the board */
	enum stone b[BOARD_MAX_COORDS];
	/* Group id the stones are part of; 0 == no group */
	group_t g[BOARD_MAX_COORDS];
	/* Positions of next stones in the stone group; 0 == last stone */
	coord_t p[BOARD_MAX_COORDS];
	/* Neighboring colors; numbers of neighbors of index color */
	struct neighbor_colors n[BOARD_MAX_COORDS];

#ifdef BOARD_PAT3
	/* 3x3 pattern code for each position; see pattern3.h for encoding
	 * specification. The information is only valid for empty points. */
FB_ONLY(hash3_t pat3)[BOARD_MAX_COORDS];
#endif

	/* Group information - indexed by gid (which is coord of base group stone) */
	struct group gi[BOARD_MAX_COORDS];

	/* List of free positions */
	/* Note that free position here is any valid move; including single-point eyes!
	 * However, pass is not included. */
FB_ONLY(coord_t f)[BOARD_MAX_COORDS];  FB_ONLY(int flen);
	/* Map free positions coords to their list index, for quick lookup. */
FB_ONLY(int fmap)[BOARD_MAX_COORDS];

#ifdef WANT_BOARD_C
	/* Queue of capturable groups */
FB_ONLY(group_t c)[BOARD_MAX_GROUPS];  FB_ONLY(int clen);
#endif

	/* Symmetry information */
FB_ONLY(struct board_symmetry symmetry);

	/* Last ko played on the board. */
FB_ONLY(struct move last_ko);
FB_ONLY(int last_ko_age);

	/* Basic ko check */
    /*基本柯尔检验*/
	struct move ko;

#ifdef BOARD_UNDO_CHECKS
	/* Guard against invalid quick_play() / quick_undo() uses */
	int quicked;
#endif
	
	/* Engine-specific state; persistent through board development,
	 * is reset only at clear_board. */
	void *es;

	/* Playout-specific state; persistent through board development,
	 * initialized by play_random_game() and free()'d at board destroy time */
	void *ps;


	/* --- PRIVATE DATA --- */

	/* For superko check: */

	/* Board "history" - hashes encountered. Size of the hash should be
	 * >> board_size^2. */
#define history_hash_bits 12
#define history_hash_mask ((1 << history_hash_bits) - 1)
#define history_hash_prev(i) ((i - 1) & history_hash_mask)
#define history_hash_next(i) ((i + 1) & history_hash_mask)
FB_ONLY(hash_t history_hash)[1 << history_hash_bits];
	/* Hash of current board position. */
    /*当前板位置的哈希。*/
FB_ONLY(hash_t hash);
	/* Hash of current board position quadrants. */
    /*当前板位置象限哈希*/
FB_ONLY(hash_t qhash)[4];
};

```







### uct_descent

```c
/* This is the state used for descending the tree; we use this wrapper
 * structure in order to be able to easily descend in multiple trees
 * in parallel (e.g. main tree and local tree) or compute cummulative
 * "path value" throughout the tree descent. */
/*这是用于降树的状态；我们使用这个包装结构以便能够在多个树中并行下降（例如主树和本地树），或者在整个树下降过程中计算累积的“路径值”。*/
struct uct_descent {
	/* Active tree nodes: */
    /*活动树节点：*/
	struct tree_node *node; /* Main tree. */
	struct tree_node *lnode; /* Local tree. */
	/* Value of main tree node (with all value factors, but unbiased
	 * - without exploration factor), from black's perspective. */
    /*从Black的角度看，主树节点的值（具有所有的值因子，但没有偏倚-没有探索因子）。*/
	struct move_stats value;
};
```

###　tree_node

```c
/* TODO: Performance would benefit from a reorganization:
 * (i) Allocate all children of a node within a single block.
 * (ii) Keep all u stats together, and all amaf stats together.
 * Currently, rave_update is top source of cache misses, and
 * there is large memory overhead for having all nodes separate. */
/*TODO:重组将使业绩受益：
*（i）在单个块中分配节点的所有子节点。
*（ii）将所有U统计和所有AMAF统计放在一起。
*目前，rave_更新是缓存未命中的首要来源，并且
*将所有节点分开会有很大的内存开销。*/
struct tree_node {
	hash_t hash;
    //这一课树是一个二叉树 还有一个父节点指针 十字链表表示法，左孩子右兄弟
	struct tree_node *parent, *sibling, *children;

	/*** From here on, struct is saved/loaded from opening tbook */

	struct move_stats u;
	struct move_stats prior;
	/* XXX: Should be way for policies to add their own stats */
	struct move_stats amaf;
	/* Stats before starting playout; used for distributed engine. */
	struct move_stats pu;
	/* Criticality information; information about final board owner
	 * of the tree coordinate corresponding to the node */
	struct move_stats winner_owner; // owner == winner
	struct move_stats black_owner; // owner == black

	/* coord is usually coord_t, but this is very space-sensitive. */
#define node_coord(n) ((int) (n)->coord)
	short coord;

	unsigned short depth; // just for statistics

	/* Number of parallel descents going through this node at the moment.
	* Used for virtual loss computation. */
	signed char descents;

	/* Common Fate Graph distance from parent, but at most TREE_NODE_D_MAX+1 */
#define TREE_NODE_D_MAX 3
	unsigned char d;

#define TREE_HINT_INVALID 1 // don't go to this node, invalid move
	unsigned char hints;

	/* In case multiple threads walk the tree, is_expanded is set
	* atomically. Only the first thread setting it expands the node.
	* The node goes through 3 states:
	*   1) children == null, is_expanded == false: leaf node
	*   2) children == null, is_expanded == true: one thread currently expanding
	*   2) children != null, is_expanded == true: fully expanded node */
    /**如果多个线程遍历树，则设置为“展开”
        *原子性。只有第一个线程设置会扩展节点。
        *节点经历3种状态：
        *1）children==null，is_expanded==false:叶节点
        *2）children==null，is_expanded==true:一个线程当前正在扩展
        *2）孩子们！=null，is_expanded==true:完全展开的节点*/
	bool is_expanded;
};

```



### uct

```c
/* How many games to consider at minimum before judging groups. */
#define GJ_MINGAMES	500

/* Internal engine state.引擎内部状态 */
struct uct {
	int debug_level;
	enum uct_reporting {
		UR_TEXT,
		UR_JSON,
		UR_JSON_BIG,
	} reporting;
	int reportfreq;

	int games, gamelen;
	floating_t resign_threshold, sure_win_threshold;
	double best2_ratio, bestr_ratio;
	floating_t max_maintime_ratio;
	bool pass_all_alive; /* Current value 当前值*/
	bool allow_losing_pass;
	bool territory_scoring;
	int expand_p;
	bool playout_amaf;
	bool amaf_prior;
	int playout_amaf_cutoff;
	double dumpthres;
	int force_seed;
	bool no_tbook;
	bool fast_alloc;
	size_t max_tree_size;
	size_t max_pruned_size;
	size_t pruning_threshold;
	int mercymin;
	int significant_threshold;//有效阈值

	int threads;
	enum uct_thread_model {
		TM_TREE, /* Tree parallelization w/o virtual loss.无虚拟损失的树并行化 */
		TM_TREEVL, /* Tree parallelization with virtual loss. 树与虚损失并行化。*/
	} thread_model;
	int virtual_loss;
	bool pondering_opt; /* User wants pondering 用户想要思考*/
	bool pondering; /* Actually pondering now 正在思考*/
	bool slave; /* Act as slave in distributed engine.在分布式引擎中充当从机 */
	int max_slaves; /* Optional, -1 if not set 可选，如果未设置-1*/
	int slave_index; /* 0..max_slaves-1, or -1 if not set 0..max_slaves-1或-1（如果未设置）*/
	enum stone my_color;

	int fuseki_end;
	int yose_start;

	int dynkomi_mask;
	int dynkomi_interval;
	struct uct_dynkomi *dynkomi;
	floating_t initial_extra_komi;

	floating_t val_scale;
	int val_points;
	bool val_extra;
	bool val_byavg;
	bool val_bytemp;
	floating_t val_bytemp_min;

	int random_policy_chance;
	bool local_tree;
	int tenuki_d;
	floating_t local_tree_aging;
#define LTREE_PLAYOUTS_MULTIPLIER 100
	floating_t local_tree_depth_decay;
	bool local_tree_allseq;
	bool local_tree_neival;
	enum {
		LTE_ROOT,
		LTE_EACH,
		LTE_TOTAL,
	} local_tree_eval;
	bool local_tree_rootchoose;

	struct {
		int level;
		int playouts;
	} debug_after;

	char *banner;

	struct uct_policy *policy;
	struct uct_policy *random_policy;
	struct playout_policy *playout;
	struct uct_prior *prior;
	struct uct_pluginset *plugins;
	struct joseki_dict *jdict;

	struct pattern_setup pat;
	/* Various modules (prior, policy, ...) set this if they want pattern
	 * database to be loaded. */
    /*各种模块（prior，policy，…）如果想要模式，就设置这个。
要加载的数据库。*/
	bool want_pat;

	/* Used within frame of single genmove. */
    /*在单个genmove的框架内使用*/
	struct board_ownermap ownermap;
	/* Used for coordination among slaves of the distributed engine. */
    /*用于分布式引擎的从机之间的协调*/
	int stats_hbits;
	int shared_nodes;
	int shared_levels;
	double stats_delay; /* stored in seconds 以秒为单位存储*/
	int played_own;
	int played_all; /* games played by all slaves 所有奴隶玩的游戏*/

	/* Saved dead groups, for final_status_list dead 所有奴隶玩的游戏*/
	struct move_queue dead_groups;
	int dead_groups_move;

	/* Game state - maintained by setup_state(), reset_state(). */
    /*游戏状态-由setup_state（）、reset_state（）维护*/
	struct tree *t;
};

```



## 函数

### init_engine函数

```c
//枚举类型， 引擎参数，棋盘
static struct engine *
init_engine(enum engine_id engine, char *e_arg, struct board *b)
{
	char *arg = e_arg? strdup(e_arg) : e_arg; //判断是否为空
	assert(engine < E_MAX);//判断是否合法
	struct engine *e = engine_init[engine](arg, b);//调用相应的初始化函数，去初始化引擎
	if (arg) free(arg);//释放空间
    //返回我们初始化的引擎
	return e;
}
```



### uct_state_init

````c
//设置uct引擎状态
struct uct *
uct_state_init(char *arg, struct board *b)
{
	struct uct *u = calloc2(1, sizeof(struct uct));
	bool pat_setup = false;
    //引擎状态参数设置
	u->debug_level = debug_level;
	u->reportfreq = 1000;
	u->gamelen = MC_GAMELEN;
	u->resign_threshold = 0.2;
	u->sure_win_threshold = 0.95;
	u->mercymin = 0;
	u->significant_threshold = 50;
	u->expand_p = 8;
	u->dumpthres = 0.01;
	u->playout_amaf = true;
	u->amaf_prior = false;
	u->max_tree_size = default_max_tree_size();
	u->fast_alloc = true;
	u->pruning_threshold = 0;

	u->threads = get_nprocessors();
	u->thread_model = TM_TREEVL;
	u->virtual_loss = 1;

	u->pondering_opt = false;

	u->fuseki_end = 20; // max time at 361*20% = 72 moves (our 36th move, still 99 to play)361*20%时的最长时间=72次移动（我们的第36次移动，仍有99次移动
	u->yose_start = 40; // (100-40-25)*361/100/2 = 63 moves still to play by us then（100-40-25）*361/100/2=63个动作由我们继续玩
	u->bestr_ratio = 0.02;
	// 2.5 is clearly too much, but seems to compensate well for overly stern time allocations.2.5显然太多了，但似乎可以很好地补偿过于严厉的时间分配。
	// TODO: Further tuning and experiments with better time allocation schemes.TODO：进一步的调整和更好的时间分配方案的实验。
	u->best2_ratio = 2.5;
	// Higher values of max_maintime_ratio sometimes cause severe time trouble in tournaments 最大保持时间比率的较高值有时会在锦标赛中造成严重的时间问题。
	// It might be necessary to reduce it to 1.5 on large board, but more tuning is needed.可能有必要在大型板上将其降低到1.5，但需要进行更多的调整。
	u->max_maintime_ratio = 2.0;


	u->val_scale = 0; u->val_points = 40;
	u->dynkomi_interval = 100;
	u->dynkomi_mask = S_BLACK | S_WHITE;

	u->tenuki_d = 4;
	u->local_tree_aging = 80;
	u->local_tree_depth_decay = 1.5;
	u->local_tree_eval = LTE_ROOT;
	u->local_tree_neival = true;

	u->max_slaves = -1;
	u->slave_index = -1;
	u->stats_delay = 0.01; // 10 ms
	u->shared_levels = 1;

	u->plugins = pluginset_init(b);

	u->jdict = joseki_load(b->size);

	if (arg) {
		char *optspec, *next = arg;
		while (*next) {
			optspec = next;
			next += strcspn(next, ",");
			if (*next) { *next++ = 0; } else { *next = 0; }

			char *optname = optspec;
			char *optval = strchr(optspec, '=');
			if (optval) *optval++ = 0;

			/** Basic options */

			if (!strcasecmp(optname, "debug")) {
				if (optval)
					u->debug_level = atoi(optval);
				else
					u->debug_level++;
			} else if (!strcasecmp(optname, "reporting") && optval) {
				/* The format of output for detailed progress
				 * information (such as current best move and
				 * its value, etc.). */
                /*详细进度信息的输出格式（如当前最佳移动及其值等）。*/
				if (!strcasecmp(optval, "text")) {
					/* Plaintext traditional output.纯文本传统输出。 */
					u->reporting = UR_TEXT;
				} else if (!strcasecmp(optval, "json")) {
					/* JSON output. Implies debug=0.JSON输出。表示debug=0。 */
					u->reporting = UR_JSON;
					u->debug_level = 0;
				} else if (!strcasecmp(optval, "jsonbig")) {
					/* JSON output, but much more detailed.
					 * Implies debug=0. JSON输出，但更详细。表示debug=0。*/
					u->reporting = UR_JSON_BIG;
					u->debug_level = 0;
				} else
					die("UCT: Invalid reporting format %s\n", optval);
			} else if (!strcasecmp(optname, "reportfreq") && optval) {
				/* The progress information line will be shown
				 * every <reportfreq> simulations. */
				u->reportfreq = atoi(optval);
			} else if (!strcasecmp(optname, "dumpthres") && optval) {
				/* When dumping the UCT tree on output, include
				 * nodes with at least this many playouts.
				 * (A fraction of the total # of playouts at the
				 * tree root.) */
				/* Use 0 to list all nodes with at least one
				 * simulation, and -1 to list _all_ nodes. */
                /*在输出上转储UCT树时，包括至少有这么多播放的节点。（三根的总决赛分数。）
使用0列出至少有一个模拟的所有节点，-1列出所有节点。*/
				u->dumpthres = atof(optval);
			} else if (!strcasecmp(optname, "resign_threshold") && optval) {
				/* Resign when this ratio of games is lost
				 * after GJ_MINGAMES sample is taken. */
                /*当这个比例的游戏在GJ Mingames抽样后丢失时辞职。*/
				u->resign_threshold = atof(optval);
			} else if (!strcasecmp(optname, "sure_win_threshold") && optval) {
				/* Stop reading when this ratio of games is won
				 * after PLAYOUT_EARLY_BREAK_MIN sample is
				 * taken. (Prevents stupid time losses,
				 * friendly to human opponents.) */
                /*当这一比例的游戏是在游戏结束后赢得的时候，停止阅读。（防止愚蠢的时间损失，对人类对手友好。）*/
				u->sure_win_threshold = atof(optval);
			} else if (!strcasecmp(optname, "force_seed") && optval) {
				/* Set RNG seed at the tree setup. */
                /*在树设置中设置RNG SEED。*/
				u->force_seed = atoi(optval);
			} else if (!strcasecmp(optname, "no_tbook")) {
				/* Disable UCT opening tbook. */
                /*禁用UCT打开tBook。*/
				u->no_tbook = true;
			} else if (!strcasecmp(optname, "pass_all_alive")) {
				/* Whether to consider passing only after all
				 * dead groups were removed from the board;
				 * this is like all genmoves are in fact
				 * kgs-genmove_cleanup. */
                /*是否只考虑在所有死亡群体从董事会中移除后才通过；这就像所有的genmoves实际上都是KGS-genmove_清理*/
				u->pass_all_alive = !optval || atoi(optval);
			} else if (!strcasecmp(optname, "allow_losing_pass")) {
				/* Whether to consider passing in a clear
				 * but losing situation, to be scored as a loss
				 * for us. */
                /*是否考虑在明确但失败的情况下传球，对我们来说是一个损失。*/
				u->allow_losing_pass = !optval || atoi(optval);
			} else if (!strcasecmp(optname, "territory_scoring")) {
				/* Use territory scoring (default is area scoring).
				 * An explicit kgs-rules command overrides this. */
                /*使用区域评分（默认为区域评分）。显式KGS规则命令重写此*/
				u->territory_scoring = !optval || atoi(optval);
			} else if (!strcasecmp(optname, "stones_only")) {
				/* Do not count eyes. Nice to teach go to kids.
				 * http://strasbourg.jeudego.org/regle_strasbourgeoise.htm */
                /*不要数数眼睛。很高兴教给孩子们。http://strasbourg.jeudego.org/regle ou strasbourgeoise.htm*/
				b->rules = RULES_STONES_ONLY;
				u->pass_all_alive = true;
			} else if (!strcasecmp(optname, "debug_after")) {
				/* debug_after=9:1000 will make Pachi think under
				 * the normal conditions, but at the point when
				 * a move is to be chosen, the tree is dumped and
				 * another 1000 simulations are run single-threaded
				 * with debug level 9, allowing inspection of Pachi's
				 * behavior after it has thought a lot. */
                /*debug after=9:1000将使pachi在正常情况下思考，但在选择移动的时候，树被转储，另外1000个模拟使用debug level 9单线程运行，允许在经过深思熟虑后检查pachi的行为。*/
				if (optval) {
					u->debug_after.level = atoi(optval);
					char *playouts = strchr(optval, ':');
					if (playouts)
						u->debug_after.playouts = atoi(playouts+1);
					else
						u->debug_after.playouts = 1000;
				} else {
					u->debug_after.level = 9;
					u->debug_after.playouts = 1000;
				}
			} else if (!strcasecmp(optname, "banner") && optval) {
				/* Additional banner string. This must come as the
				 * last engine parameter. You can use '+' instead
				 * of ' ' if you are wrestling with kgsGtp. */
                /*字符串附加的旗帜。this as the last必备的发动机参数。你可以使用instead of +如果你是摔跤与kgsgtp*/
				if (*next) *--next = ',';
				u->banner = strdup(optval);
				for (char *b = u->banner; *b; b++) {
					if (*b == '+') *b = ' ';
				}
				break;
			} else if (!strcasecmp(optname, "plugin") && optval) {
				/* Load an external plugin; filename goes before the colon,
				 * extra arguments after the colon. */
                /*加载外部插件；文件名位于冒号之前，Xtra参数位于冒号之后。*/
				char *pluginarg = strchr(optval, ':');
				if (pluginarg)
					*pluginarg++ = 0;
				plugin_load(u->plugins, optval, pluginarg);

			/** UCT behavior and policies */
            /*UCT行为和政策*/

			} else if ((!strcasecmp(optname, "policy")
				/* Node selection policy. ucb1amaf is the
				 * default policy implementing RAVE, while
				 * ucb1 is the simple exploration/exploitation
				 * policy. Policies can take further extra
				 * options. */
                 /*节点选择策略。UCB1AMAF是实现RAVE的默认策略，而UCB1是简单的勘探/开发策略。政策可以采取进一步的额外选择。*/
			            || !strcasecmp(optname, "random_policy")) && optval) {
				/* A policy to be used randomly with small
				 * chance instead of the default policy. */
                /*一种随机使用的策略，机会很小，而不是默认策略*/
				char *policyarg = strchr(optval, ':');
				struct uct_policy **p = !strcasecmp(optname, "policy") ? &u->policy : &u->random_policy;
				if (policyarg)
					*policyarg++ = 0;
				if (!strcasecmp(optval, "ucb1")) {
					*p = policy_ucb1_init(u, policyarg);
				} else if (!strcasecmp(optval, "ucb1amaf")) {
					*p = policy_ucb1amaf_init(u, policyarg, b);
				} else
					die("UCT: Invalid tree policy %s\n", optval);
			} else if (!strcasecmp(optname, "playout") && optval) {
				/* Random simulation (playout) policy.
				 * moggy is the default policy with large
				 * amount of domain-specific knowledge and
				 * heuristics. light is a simple uniformly
				 * random move selection policy. */
                /*随机模拟（播放）策略.moggy是默认策略领域特定知识和启发式方法的数量。光是一个简单的统一和移动选择政策。*/
				char *playoutarg = strchr(optval, ':');
				if (playoutarg)
					*playoutarg++ = 0;
				if (!strcasecmp(optval, "moggy")) {
					u->playout = playout_moggy_init(playoutarg, b, u->jdict);
				} else if (!strcasecmp(optval, "light")) {
					u->playout = playout_light_init(playoutarg, b);
				} else
					die("UCT: Invalid playout policy %s\n", optval);
			} else if (!strcasecmp(optname, "prior") && optval) {
				/* Node priors policy. When expanding a node,
				 * it will seed node values heuristically
				 * (most importantly, based on playout policy
				 * opinion, but also with regard to other
				 * things). See uct/prior.c for details.
				 * Use prior=eqex=0 to disable priors. */
                /*节点优先策略。当扩展一个节点时，它将以启发式方式（最重要的是，基于播放策略的意见，但也涉及到其他事情）种子节点值。详见UCT/Prior.C。使用prior=eqex=0禁用prior。*/
				u->prior = uct_prior_init(optval, b, u);
			} else if (!strcasecmp(optname, "mercy") && optval) {
				/* Minimal difference of black/white captures
				 * to stop playout - "Mercy Rule". Speeds up
				 * hopeless playouts at the expense of some
				 * accuracy. */
                /*黑白截图的最小差异，以阻止播放-“仁慈规则”。以一定的准确性加速无望的决赛。*/
				u->mercymin = atoi(optval);
			} else if (!strcasecmp(optname, "gamelen") && optval) {
				/* Maximum length of single simulation
				 * in moves. */
                /*移动中单个模拟的最大长度。*/
				u->gamelen = atoi(optval);
			} else if (!strcasecmp(optname, "expand_p") && optval) {
				/* Expand UCT nodes after it has been
				 * visited this many times. */
                /*在多次访问之后展开UCT节点。*/
				u->expand_p = atoi(optval);
			} else if (!strcasecmp(optname, "random_policy_chance") && optval) {
				/* If specified (N), with probability 1/N, random_policy policy
				 * descend is used instead of main policy descend; useful
				 * if specified policy (e.g. UCB1AMAF) can make unduly biased
				 * choices sometimes, you can fall back to e.g.
				 * random_policy=UCB1. */
                /*如果指定了（n），概率为1/n，则使用随机策略下降而不是主策略下降；如果指定的策略（例如UCB1AMAF）有时会做出过度偏向的选择，则很有用，您可以返回到随机策略=UCB1。*/
				u->random_policy_chance = atoi(optval);

			/** General AMAF behavior */
			/* (Only relevant if the policy supports AMAF.
			 * More variables can be tuned as policy
			 * parameters.) */
			/*一般AMAF行为*/
			/*（仅当政策支持AMAF时才相关。
			*更多变量可以作为策略进行调整
			*参数。）*/
			} else if (!strcasecmp(optname, "playout_amaf")) {
				/* Whether to include random playout moves in
				 * AMAF as well. (Otherwise, only tree moves
				 * are included in AMAF. Of course makes sense
				 * only in connection with an AMAF policy.) */
				/* with-without: 55.5% (+-4.1) */
                /*是否包含随机播放
				AAMF也是如此。（否则，只有树移动
				包含在AMAF中。当然有道理
				仅与AMAF政策相关。）不含：55.5%（+-4.1）*/
				if (optval && *optval == '0')
					u->playout_amaf = false;
				else
					u->playout_amaf = true;
			} else if (!strcasecmp(optname, "playout_amaf_cutoff") && optval) {
				/* Keep only first N% of playout stage AMAF
				 * information. */
                /*仅保留播放阶段AMAF信息的前n%。*/
				u->playout_amaf_cutoff = atoi(optval);
			} else if (!strcasecmp(optname, "amaf_prior") && optval) {
				/* In node policy, consider prior values
				 * part of the real result term or part
				 * of the AMAF term? */
                /*在节点策略中，考虑先验值是实际结果项的一部分还是AMAF项的一部分？*/
				u->amaf_prior = atoi(optval);

			/** Performance and memory management */
			/*性能和内存管理*/
			} else if (!strcasecmp(optname, "threads") && optval) {
				/* By default, Pachi will run with only single
				 * tree search thread! */
                /*默认情况下，pachi只运行一个树搜索线程！*/
				u->threads = atoi(optval);
			} else if (!strcasecmp(optname, "thread_model") && optval) {
				if (!strcasecmp(optval, "tree")) {
					/* Tree parallelization - all threads
					 * grind on the same tree. */
                    /*树并行化-所有线程在同一棵树上研磨。*/
					u->thread_model = TM_TREE;
					u->virtual_loss = 0;
				} else if (!strcasecmp(optval, "treevl")) {
					/* Tree parallelization, but also
					 * with virtual losses - this discou-
					 * rages most threads choosing the
					 * same tree branches to read. */
                    /*树并行化，但也有虚拟的损失-这使大多数线程无法选择要读取的同一个树分支。*/
					u->thread_model = TM_TREEVL;
				} else
					die("UCT: Invalid thread model %s\n", optval);
			} else if (!strcasecmp(optname, "virtual_loss") && optval) {
				/* Number of virtual losses added before evaluating a node. */
				u->virtual_loss = atoi(optval);
			} else if (!strcasecmp(optname, "pondering")) {
				/* Keep searching even during opponent's turn. */
                /*即使在对手转弯时也要继续搜索。*/
				u->pondering_opt = !optval || atoi(optval);
			} else if (!strcasecmp(optname, "max_tree_size") && optval) {
				/* Maximum amount of memory [MiB] consumed by the move tree.
				 * For fast_alloc it includes the temp tree used for pruning.
				 * Default is 3072 (3 GiB). */
                /*移动树消耗的最大内存量[MIB]。对于快速分配，它包括用于修剪的临时树。默认值为3072（3 GiB）*/
				u->max_tree_size = (size_t)atoll(optval) * 1048576;  /* long is 4 bytes on windows! */
			} else if (!strcasecmp(optname, "fast_alloc")) {
				u->fast_alloc = !optval || atoi(optval);
			} else if (!strcasecmp(optname, "pruning_threshold") && optval) {
				/* Force pruning at beginning of a move if the tree consumes
				 * more than this [MiB]. Default is 10% of max_tree_size.
				 * Increase to reduce pruning time overhead if memory is plentiful.
				 * This option is meaningful only for fast_alloc. */
                /*如果树的消耗量超过此[mib]，则在移动开始时强制修剪。默认值是max_tree_大小的10%。如果内存充足，请增加以减少修剪时间开销。此选项仅对快速分配有意义*/
				u->pruning_threshold = atol(optval) * 1048576;

			/** Time control */
           	/*时间控制*/

			} else if (!strcasecmp(optname, "best2_ratio") && optval) {
				/* If set, prolong simulating while
				 * first_best/second_best playouts ratio
				 * is less than best2_ratio. */
                /*如果设置了，则延长模拟时间，而第一次最佳/第二次最佳出局率小于最佳2出局率。*/
				u->best2_ratio = atof(optval);
			} else if (!strcasecmp(optname, "bestr_ratio") && optval) {
				/* If set, prolong simulating while
				 * best,best_best_child values delta
				 * is more than bestr_ratio. */
                /*如果设置，则在最佳的情况下延长模拟时间，最佳子值delta大于最佳比值。*/
				u->bestr_ratio = atof(optval);
			} else if (!strcasecmp(optname, "max_maintime_ratio") && optval) {
				/* If set and while not in byoyomi, prolong simulating no more than
				 * max_maintime_ratio times the normal desired thinking time. */
                /*如果设置了且不在Byoyomi中，则延长模拟时间不超过最大维护时间与正常期望思考时间的比值。*/
				u->max_maintime_ratio = atof(optval);
			} else if (!strcasecmp(optname, "fuseki_end") && optval) {
				/* At the very beginning it's not worth thinking
				 * too long because the playout evaluations are
				 * very noisy. So gradually increase the thinking
				 * time up to maximum when fuseki_end percent
				 * of the board has been played.
				 * This only applies if we are not in byoyomi. */
                /*一开始不值得考虑太长时间，因为决赛评估非常嘈杂。因此，逐渐增加思考时间，直到最长的时候，fuseki ou结束百分比的董事会已经发挥。这只适用于我们不在byoyomi。*/
				u->fuseki_end = atoi(optval);
			} else if (!strcasecmp(optname, "yose_start") && optval) {
				/* When yose_start percent of the board has been
				 * played, or if we are in byoyomi, stop spending
				 * more time and spread the remaining time
				 * uniformly.
				 * Between fuseki_end and yose_start, we spend
				 * a constant proportion of the remaining time
				 * on each move. (yose_start should actually
				 * be much earlier than when real yose start,
				 * but "yose" is a good short name to convey
				 * the idea.) */
                /*当游戏开始时，或者如果我们在Byoyomi，停止花费更多的时间，并将剩余的时间均匀分布。在Fuseki ou end和Yose ou start之间，我们将剩余时间的恒定比例花在每个动作上。（yose-start实际上应该比真正的yose-start早得多，但是“yose”是一个很好的简短名称来表达这个想法。）*/
				u->yose_start = atoi(optval);

			/** Dynamic komi */
            /*动态科米*/

			} else if (!strcasecmp(optname, "dynkomi") && optval) {
				/* Dynamic komi approach; there are multiple
				 * ways to adjust komi dynamically throughout
				 * play. We currently support two: */
                /*动态Komi方法；有多种方法可以在整个比赛中动态调整Komi。我们目前支持两种：*/
				char *dynkomiarg = strchr(optval, ':');
				if (dynkomiarg)
					*dynkomiarg++ = 0;
				if (!strcasecmp(optval, "none")) {
					u->dynkomi = uct_dynkomi_init_none(u, dynkomiarg, b);
				} else if (!strcasecmp(optval, "linear")) {
					/* You should set dynkomi_mask=1 or a very low
					 * handicap_value for white. */
                    /*您应该为白色设置dynkomi_mask=1或非常低的残疾值。*/
					u->dynkomi = uct_dynkomi_init_linear(u, dynkomiarg, b);
				} else if (!strcasecmp(optval, "adaptive")) {
					/* There are many more knobs to
					 * crank - see uct/dynkomi.c. */
                    /*还有很多旋钮需要转动-参见UCT/Dynkomi.c.*/
					u->dynkomi = uct_dynkomi_init_adaptive(u, dynkomiarg, b);
				} else
					die("UCT: Invalid dynkomi mode %s\n", optval);
			} else if (!strcasecmp(optname, "dynkomi_mask") && optval) {
				/* Bitmask of colors the player must be
				 * for dynkomi be applied; the default dynkomi_mask=3 allows
				 * dynkomi even in games where Pachi is white. */
                /*颜色的位掩码应用dynkomi之前玩家必须使用；默认dynkomi_mask=3允许dynkomi，即使在pachi为白色的游戏中也是如此。*/
				u->dynkomi_mask = atoi(optval);
			} else if (!strcasecmp(optname, "dynkomi_interval") && optval) {
				/* If non-zero, re-adjust dynamic komi
				 * throughout a single genmove reading,
				 * roughly every N simulations. */
				/* XXX: Does not work with tree
				 * parallelization. */
                /*如果非零，重新调整动态Komithroughout一个单一的genmove读数，大致每N次模拟。不适用于树并行化。*/
				u->dynkomi_interval = atoi(optval);
			} else if (!strcasecmp(optname, "extra_komi") && optval) {
				/* Initial dynamic komi settings. This
				 * is useful for the adaptive dynkomi
				 * policy as the value to start with
				 * (this is NOT kept fixed) in case
				 * there is not enough time in the search
				 * to adjust the value properly (e.g. the
				 * game was interrupted). */
                /*初始动态Komi设置。这对于自适应Dynkomi策略很有用，因为如果搜索中没有足够的时间来正确调整值（例如游戏被中断），则该策略将作为开始的值（该值不保持固定）。*/
				u->initial_extra_komi = atof(optval);

			/** Node value result scaling */
            /*节点值结果缩放*/

			} else if (!strcasecmp(optname, "val_scale") && optval) {
				/* How much of the game result value should be
				 * influenced by win size. Zero means it isn't. */
                /*游戏结果值的多少应该受赢的大小的影响。零意味着不是。*/
                u->val_scale = atof(optval);
			} else if (!strcasecmp(optname, "val_points") && optval) {
				/* Maximum size of win to be scaled into game
				 * result value. Zero means boardsize^2. */
                /*将要缩放到游戏结果值中的最大胜利大小。零表示板大小^2。*/
				u->val_points = atoi(optval) * 2; // result values are doubled
			} else if (!strcasecmp(optname, "val_extra")) {
				/* If false, the score coefficient will be simply
				 * added to the value, instead of scaling the result
				 * coefficient because of it. */
                /*如果为false，则分数系数将简单地添加到值中，而不是因为该值而缩放结果系数。*/
				u->val_extra = !optval || atoi(optval);
			} else if (!strcasecmp(optname, "val_byavg")) {
				/* If true, the score included in the value will
				 * be relative to average score in the current
				 * search episode inst. of jigo. */
                /*如果为真，该值中包含的分数将与jigo当前搜索集inst.中的平均分数相对应。*/
				u->val_byavg = !optval || atoi(optval);
			} else if (!strcasecmp(optname, "val_bytemp")) {
				/* If true, the value scaling coefficient
				 * is different based on value extremity
				 * (dist. from 0.5), linear between
				 * val_bytemp_min, val_scale. */
                /*如果为真，则值缩放系数根据值极限（从0.5开始的距离）而不同，在Val_Bytemp_Min、Val_Scale之间为线性。*/
				u->val_bytemp = !optval || atoi(optval);
			} else if (!strcasecmp(optname, "val_bytemp_min") && optval) {
				/* Minimum val_scale in case of val_bytemp. */
				u->val_bytemp_min = atof(optval);

			/** Local trees */
			/* (Purely experimental. Does not work - yet!) */

			} else if (!strcasecmp(optname, "local_tree")) {
				/* Whether to bias exploration by local tree values. */
				u->local_tree = !optval || atoi(optval);
			} else if (!strcasecmp(optname, "tenuki_d") && optval) {
				/* Tenuki distance at which to break the local tree. */
				u->tenuki_d = atoi(optval);
				if (u->tenuki_d > TREE_NODE_D_MAX + 1)
					die("uct: tenuki_d must not be larger than TREE_NODE_D_MAX+1 %d\n", TREE_NODE_D_MAX + 1);
			} else if (!strcasecmp(optname, "local_tree_aging") && optval) {
				/* How much to reduce local tree values between moves. */
				u->local_tree_aging = atof(optval);
			} else if (!strcasecmp(optname, "local_tree_depth_decay") && optval) {
				/* With value x>0, during the descent the node
				 * contributes 1/x^depth playouts in
				 * the local tree. I.e., with x>1, nodes more
				 * distant from local situation contribute more
				 * than nodes near the root. */
				u->local_tree_depth_decay = atof(optval);
			} else if (!strcasecmp(optname, "local_tree_allseq")) {
				/* If disabled, only complete sequences are stored
				 * in the local tree. If this is on, also
				 * subsequences starting at each move are stored. */
				u->local_tree_allseq = !optval || atoi(optval);
			} else if (!strcasecmp(optname, "local_tree_neival")) {
				/* If disabled, local node value is not
				 * computed just based on terminal status
				 * of the coordinate, but also its neighbors. */
				u->local_tree_neival = !optval || atoi(optval);
			} else if (!strcasecmp(optname, "local_tree_eval")) {
				/* How is the value inserted in the local tree
				 * determined. */
				if (!strcasecmp(optval, "root"))
					/* All moves within a tree branch are
					 * considered wrt. their merit
					 * reaching tachtical goal of making
					 * the first move in the branch
					 * survive. */
					u->local_tree_eval = LTE_ROOT;
				else if (!strcasecmp(optval, "each"))
					/* Each move is considered wrt.
					 * its own survival. */
					u->local_tree_eval = LTE_EACH;
				else if (!strcasecmp(optval, "total"))
					/* The tactical goal is the survival
					 * of all the moves of my color and
					 * non-survival of all the opponent
					 * moves. Local values (and their
					 * inverses) are averaged. */
					u->local_tree_eval = LTE_TOTAL;
				else
					die("uct: unknown local_tree_eval %s\n", optval);
			} else if (!strcasecmp(optname, "local_tree_rootchoose")) {
				/* If disabled, only moves within the local
				 * tree branch are considered; the values
				 * of the branch roots (i.e. root children)
				 * are ignored. This may make sense together
				 * with eval!=each, we consider only moves
				 * that influence the goal, not the "rating"
				 * of the goal itself. (The real solution
				 * will be probably using criticality to pick
				 * local tree branches.) */
				u->local_tree_rootchoose = !optval || atoi(optval);

			/** Other heuristics */
			} else if (!strcasecmp(optname, "patterns")) {
				/* Load pattern database. Various modules
				 * (priors, policies etc.) may make use
				 * of this database. They will request
				 * it automatically in that case, but you
				 * can use this option to tweak the pattern
				 * parameters. */
				patterns_init(&u->pat, optval, false, true);
				u->want_pat = pat_setup = true;
			} else if (!strcasecmp(optname, "significant_threshold") && optval) {
				/* Some heuristics (XXX: none in mainline) rely
				 * on the knowledge of the last "significant"
				 * node in the descent. Such a node is
				 * considered reasonably trustworthy to carry
				 * some meaningful information in the values
				 * of the node and its children. */
				u->significant_threshold = atoi(optval);

			/** Distributed engine slaves setup */

			} else if (!strcasecmp(optname, "slave")) {
				/* Act as slave for the distributed engine. */
				u->slave = !optval || atoi(optval);
			} else if (!strcasecmp(optname, "slave_index") && optval) {
				/* Optional index if per-slave behavior is desired.
				 * Must be given as index/max */
				u->slave_index = atoi(optval);
				char *p = strchr(optval, '/');
				if (p) u->max_slaves = atoi(++p);
			} else if (!strcasecmp(optname, "shared_nodes") && optval) {
				/* Share at most shared_nodes between master and slave at each genmoves.
				 * Must use the same value in master and slaves. */
				u->shared_nodes = atoi(optval);
			} else if (!strcasecmp(optname, "shared_levels") && optval) {
				/* Share only nodes of level <= shared_levels. */
				u->shared_levels = atoi(optval);
			} else if (!strcasecmp(optname, "stats_hbits") && optval) {
				/* Set hash table size to 2^stats_hbits for the shared stats. */
				u->stats_hbits = atoi(optval);
			} else if (!strcasecmp(optname, "stats_delay") && optval) {
				/* How long to wait in slave for initial stats to build up before
				 * replying to the genmoves command (in ms) */
				u->stats_delay = 0.001 * atof(optval);

			/** Presets */

			} else if (!strcasecmp(optname, "maximize_score")) {
				/* A combination of settings that will make
				 * Pachi try to maximize his points (instead
				 * of playing slack yose) or minimize his loss
				 * (and proceed to counting even when losing). */
				/* Please note that this preset might be
				 * somewhat weaker than normal Pachi, and the
				 * score maximization is approximate; point size
				 * of win/loss still should not be used to judge
				 * strength of Pachi or the opponent. */
				/* See README for some further notes. */
				if (!optval || atoi(optval)) {
					/* Allow scoring a lost game. */
					u->allow_losing_pass = true;
					/* Make Pachi keep his calm when losing
					 * and/or maintain winning marging. */
					/* Do not play games that are losing
					 * by too much. */
					/* XXX: komi_ratchet_age=40000 is necessary
					 * with losing_komi_ratchet, but 40000
					 * is somewhat arbitrary value. */
					char dynkomi_args[] = "losing_komi_ratchet:komi_ratchet_age=60000:no_komi_at_game_end=0:max_losing_komi=30";
					u->dynkomi = uct_dynkomi_init_adaptive(u, dynkomi_args, b);
					/* XXX: Values arbitrary so far. */
					/* XXX: Also, is bytemp sensible when
					 * combined with dynamic komi?! */
					u->val_scale = 0.01;
					u->val_bytemp = true;
					u->val_bytemp_min = 0.001;
					u->val_byavg = true;
				}

			} else
				die("uct: Invalid engine argument %s or missing value\n", optname);
		}
	}

	if (!u->policy)
		u->policy = policy_ucb1amaf_init(u, NULL, b);

	if (!!u->random_policy_chance ^ !!u->random_policy)
		die("uct: Only one of random_policy and random_policy_chance is set\n");

	if (!u->local_tree) {
		/* No ltree aging. */
		u->local_tree_aging = 1.0f;
	}

	if (u->fast_alloc) {
		if (u->pruning_threshold < u->max_tree_size / 10)
			u->pruning_threshold = u->max_tree_size / 10;
		if (u->pruning_threshold > u->max_tree_size / 2)
			u->pruning_threshold = u->max_tree_size / 2;

		/* Limit pruning temp space to 20% of memory. Beyond this we discard
		 * the nodes and recompute them at the next move if necessary. */
		u->max_pruned_size = u->max_tree_size / 5;
		u->max_tree_size -= u->max_pruned_size;
	} else {
		/* Reserve 5% memory in case the background free() are slower
		 * than the concurrent allocations. */
		u->max_tree_size -= u->max_tree_size / 20;
	}

	if (!u->prior)
		u->prior = uct_prior_init(NULL, b, u);

	if (!u->playout)
		u->playout = playout_moggy_init(NULL, b, u->jdict);
	if (!u->playout->debug_level)
		u->playout->debug_level = u->debug_level;

	if (u->want_pat && !pat_setup)
		patterns_init(&u->pat, NULL, false, true);
	dcnn_init();
	log_nthreads(u);

	if (u->slave) {
		if (!u->stats_hbits) u->stats_hbits = DEFAULT_STATS_HBITS;
		if (!u->shared_nodes) u->shared_nodes = DEFAULT_SHARED_NODES;
		assert(u->shared_levels * board_bits2(b) <= 8 * (int)sizeof(path_t));
	}

	if (!u->dynkomi)
		u->dynkomi = board_small(b) ? uct_dynkomi_init_none(u, NULL, b)
			: uct_dynkomi_init_linear(u, NULL, b);

	if (u->pondering_opt && using_dcnn(b)) {
		warning("Can't use pondering with dcnn right now, pondering turned off.\n");
		u->pondering_opt = false;
	}

	/* Some things remain uninitialized for now - the opening tbook
	 * is not loaded and the tree not set up. */
	/* This will be initialized in setup_state() at the first move
	 * received/requested. This is because right now we are not aware
	 * about any komi or handicap setup and such. */

	return u;
}

````

### uct_notify

```c
//通知
enum parse_code
uct_notify(struct engine *e, struct board *b, int id, char *cmd, char *args, char **reply)
{
	struct uct *u = e->data;

	static bool board_resized = true;
	if (is_gamestart(cmd)) {
		board_resized = true;
		uct_pondering_stop(u);
	}

	/* Force resending the whole command history if we are out of sync
	 * but do it only once, not if already getting the history. */
    /*如果不同步，则强制重新发送整个命令历史记录，但只执行一次，如果已经获取了历史记录，则不执行此操作。*/
	if ((move_number(id) != b->moves || !board_resized)
	    && !reply_disabled(id) && !is_reset(cmd)) {
		static char buf[128];
		snprintf(buf, sizeof(buf), "Out of sync, %d %s, move %d expected", id, cmd, b->moves);
		if (UDEBUGL(0))
			fprintf(stderr, "%s\n", buf); 
		discard_bin_args(args);

		*reply = buf;
		/* Let gtp_parse() complain about invalid commands. */
		if (!gtp_is_valid(e, cmd) && !is_repeated(cmd)) return P_OK;
		return P_DONE_ERROR;
	}
	return reply_disabled(id) ? P_NOREPLY : P_OK;
}
```

### known_commands

```c
/* List of public gtp commands. The internal command pachi-genmoves is not exported,
 * it should only be used between master and slaves of the distributed engine.
 * For now only uct engine supports gogui-analyze_commands. */
/*公共GTP命令列表。内部命令pachi genmoves不导出，只能在分布式引擎的主引擎和从引擎之间使用，目前只有UCT引擎支持gogui-analyze_命令。*/
static char*
known_commands(struct engine *engine)
{
	static char buf[8192];
	char *str = buf;
	
	for (int i = 0; commands[i].cmd; i++) {
		char *cmd = commands[i].cmd;	
        //str_prefix 字节比较
		if (str_prefix("gogui", cmd) ||
		    str_prefix("pachi-genmoves", cmd))
			continue;		
		str += sprintf(str, "%s\n", commands[i].cmd);
	}
	
	str += sprintf(str, "gogui-analyze_commands\n");
	str[-1] = 0;  /* remove last \n */
	return buf;
}
```



### uct_genmove

```c

```

### time_now

```c
/* Returns the current time. */
/*返回当前时间*/
double
time_now(void)
{
#if _POSIX_TIMERS > 0
	struct timespec now;
    //CLOCK_REALTIME 统当前时间，从1970年1.1日算起
	clock_gettime(CLOCK_REALTIME, &now);
    //第一个是秒，第二个是纳秒
	return now.tv_sec + now.tv_nsec/1000000000.0;
#else
    //一个是秒，一个是微秒
	struct timeval now;
    //获取系统时间
	gettimeofday(&now, NULL);
	return now.tv_sec + now.tv_usec/1000000.0;
#endif
}
```



### uct_search_games

```c
int
uct_search_games(struct uct_search_state *s)
{
	return s->ctx->t->root->u.playouts;
}
//追踪：
/* Progress information of the on-going MCTS search - when did we
 * last adjusted dynkomi, printed out stuff, etc. */
/*正在进行的MCTS搜索的进度信息-我们上次调整Dynkomi、打印出的内容等是什么时候？*/
struct uct_search_state {
	/* Number of games simulated for this simulation before
	 * we started the search. (We have simulated them earlier.) */
    /*在我们开始搜索之前为此模拟模拟模拟的游戏数。（我们之前已经对它们进行了模拟。）*/
	int base_playouts;
	/* Number of last dynkomi adjustment. */
    /*上次Dynkomi调整的次数。*/
	int last_dynkomi;
	/* Number of last game with progress print. */
    /*带有进度打印的上一个游戏的数目。*/
	int last_print;
	/* Number of simulations to wait before next print. */
    /*下次打印前等待的模拟数。*/
	int print_interval;
	/* Printed notification about full memory? */
    /*关于内存已满的打印通知*/
	bool fullmem;

	struct time_stop stop;
	struct uct_thread_ctx *ctx;
};

/* Search thread context */
/*搜索线程上下文*/
struct uct_thread_ctx {
	int tid; //线程id
	struct uct *u;//引擎中的数据，传入字引擎
	struct board *b;//棋盘大小
	enum stone color;//执子颜色
	struct tree *t;//蒙特卡洛树
	unsigned long seed;//随机种子
	int games;//总共玩了多少次//传出参数
	struct time_info *ti;//时间限制
};



struct tree {
	struct board *board;
	struct tree_node *root;//这个才是树 其他的都是树的属性
	struct board_symmetry root_symmetry;
	enum stone root_color;

	/* Whether to use any extra komi during score counting. This is
	 * tree-specific variable since this can arbitrarily change between
	 * moves. */
	bool use_extra_komi;
	/* A single-move-valid flag that marks a tree that is potentially
	 * badly skewed and should be used with care. Currently, we never
	 * resign on untrustworthy_tree and do not reuse the tree on next
	 * move. */
	bool untrustworthy_tree;
	/* The value of applied extra komi. For DYNKOMI_LINEAR, this value
	 * is only informative, the actual value is computed per simulation
	 * based on leaf node depth. */
	floating_t extra_komi;
	/* Score in simulations, averaged over all branches, in the last
	 * search episode. */
	struct move_stats avg_score;

	/* We merge local (non-tenuki) sequences for both colors, occuring
	 * anywhere in the tree; nodes are created on-demand, special 'pass'
	 * nodes represent tenuki. Only u move_stats are used, prior and amaf
	 * is ignored. Values in root node are ignored. */
	/* The value corresponds to black-to-play as usual; i.e. if white
	 * succeeds in its replies, the values will be low. */
    /*我们合并两种颜色的局部（非Tenuki）序列，发生
        *树中的任意位置；节点按需创建，特殊的“pass”
        *节点表示Tenuki。仅使用u move_stats，prior和amaf
        *被忽略。根节点中的值将被忽略。*/
        /*该值与黑色对应，以正常播放；即，如果为白色
         * *回复成功，数值会很低。*/
	struct tree_node *ltree_black;
	/* ltree_white has white-first sequences as children. */
	struct tree_node *ltree_white;
	/* Aging factor; 2 means halve all playout values after each turn.
	 * 1 means don't age at all. */
	floating_t ltree_aging;

	/* Hash table used when working as slave for the distributed engine.
	 * Maps coordinate path to tree node. */
    /*作为分布式引擎的从机时使用的哈希表。将坐标路径映射到树节点*/
	struct tree_hash *htable;
	int hbits;

	// Statistics
	int max_depth;
	volatile size_t nodes_size; // byte size of all allocated nodes
	size_t max_tree_size; // maximum byte size for entire tree, > 0 only for fast_alloc
	size_t max_pruned_size;
	size_t pruning_threshold;
	void *nodes; // nodes buffer, only for fast_alloc
};



/* TODO: Performance would benefit from a reorganization:
 * (i) Allocate all children of a node within a single block.
 * (ii) Keep all u stats together, and all amaf stats together.
 * Currently, rave_update is top source of cache misses, and
 * there is large memory overhead for having all nodes separate. */
/*TODO:重组将使业绩受益：
*（i）在单个块中分配节点的所有子节点。
*（ii）将所有U统计和所有AMAF统计放在一起。
*目前，rave_更新是缓存未命中的首要来源，并且
*将所有节点分开会有很大的内存开销。*/
struct tree_node {
	hash_t hash;
    //这一课树是一个二叉树 还有一个父节点指针 十字链表表示法，左孩子右兄弟
	struct tree_node *parent, *sibling, *children;

	/*** From here on, struct is saved/loaded from opening tbook */

	struct move_stats u;
	struct move_stats prior;
	/* XXX: Should be way for policies to add their own stats */
	struct move_stats amaf;
	/* Stats before starting playout; used for distributed engine. */
	struct move_stats pu;
	/* Criticality information; information about final board owner
	 * of the tree coordinate corresponding to the node */
	struct move_stats winner_owner; // owner == winner
	struct move_stats black_owner; // owner == black

	/* coord is usually coord_t, but this is very space-sensitive. */
#define node_coord(n) ((int) (n)->coord)
	short coord;

	unsigned short depth; // just for statistics

	/* Number of parallel descents going through this node at the moment.
	* Used for virtual loss computation. */
	signed char descents;

	/* Common Fate Graph distance from parent, but at most TREE_NODE_D_MAX+1 */
#define TREE_NODE_D_MAX 3
	unsigned char d;

#define TREE_HINT_INVALID 1 // don't go to this node, invalid move
	unsigned char hints;

	/* In case multiple threads walk the tree, is_expanded is set
	* atomically. Only the first thread setting it expands the node.
	* The node goes through 3 states:
	*   1) children == null, is_expanded == false: leaf node
	*   2) children == null, is_expanded == true: one thread currently expanding
	*   2) children != null, is_expanded == true: fully expanded node */
    /**如果多个线程遍历树，则设置为“展开”
        *原子性。只有第一个线程设置会扩展节点。
        *节点经历3种状态：
        *1）children==null，is_expanded==false:叶节点
        *2）children==null，is_expanded==true:一个线程当前正在扩展
        *2）孩子们！=null，is_expanded==true:完全展开的节点*/
	bool is_expanded;
};


//floating_t 是 float  赢得次数 玩的总次数，
struct move_stats {
	floating_t value; // BLACK wins/playouts
	int playouts; // # of playouts
};

```



### uct_search_progress

```c
//进展
void
uct_search_progress(struct uct *u, struct board *b, enum stone color,
		    struct tree *t, struct time_info *ti,
		    struct uct_search_state *s, int i)
{
	struct uct_thread_ctx *ctx = s->ctx;

	/* Adjust dynkomi? */
	int di = u->dynkomi_interval * u->threads;
	if (ctx->t->use_extra_komi && u->dynkomi->permove
	    && !u->pondering && di
	    && i > s->last_dynkomi + di) {
		s->last_dynkomi += di;
		floating_t old_dynkomi = ctx->t->extra_komi;
		ctx->t->extra_komi = u->dynkomi->permove(u->dynkomi, b, ctx->t);
		if (UDEBUGL(3) && old_dynkomi != ctx->t->extra_komi)
			fprintf(stderr, "dynkomi adjusted (%f -> %f)\n",
				old_dynkomi, ctx->t->extra_komi);
	}

	/* Print progress? */
    /*打印进度*/
	if (i - s->last_print > s->print_interval) {
		s->last_print += s->print_interval; // keep the numbers tidy 保持数tidy
		uct_progress_status(u, ctx->t, color, s->last_print, NULL);
	}

	if (!s->fullmem && ctx->t->nodes_size > u->max_tree_size) {
		char *msg = "WARNING: Tree memory limit reached, stopping search.\n"
			    "Try increasing max_tree_size.\n";
		if (UDEBUGL(2))  fprintf(stderr, "%s", msg);
#ifdef _WIN32
		popup(msg);
#endif
		s->fullmem = true;
	}
}

```



### uct_progress_status

```c
void
uct_progress_status(struct uct *u, struct tree *t, enum stone color, int playouts, coord_t *final)
{
	switch (u->reporting) {
		case UR_TEXT:
			uct_progress_text(u, t, color, playouts);
			break;
		case UR_JSON:
		case UR_JSON_BIG:
			uct_progress_json(u, t, color, playouts, final,
			                  u->reporting == UR_JSON_BIG);
			break;
		default: assert(0);
	}

	if (!gogui_livegfx)
		return;

	char buffer[10000];  strbuf_t strbuf;
	strbuf_t *buf = strbuf_init(&strbuf, buffer, sizeof(buffer));

	switch(gogui_livegfx) {
		case UR_GOGUI_BEST:
			uct_progress_gogui_best(buf, u, t, color, playouts);
			break;
		case UR_GOGUI_SEQ:
			uct_progress_gogui_sequence(buf, u, t, color, playouts);
			break;
		case UR_GOGUI_WR:
			uct_progress_gogui_winrates(buf, u, t, color, playouts);
			break;
		default: assert(0);
	}

	gogui_show_livegfx(buf->str);
}
```



### uct_progress_text

```c
void
uct_progress_text(struct uct *u, struct tree *t, enum stone color, int playouts)
{
	struct board *b = t->board;
	if (!UDEBUGL(0))
		return;

	/* Best move */
	struct tree_node *best = u->policy->choose(u->policy, t->root, b, color, resign);
	if (!best) {
		fprintf(stderr, "... No moves left\n");
		return;
	}
	fprintf(stderr, "[%d] ", playouts);
	fprintf(stderr, "best %.1f%% ", 100 * tree_node_get_value(t, 1, best->u.value));

	/* Dynamic komi */
	if (t->use_extra_komi)
		fprintf(stderr, "xkomi %.1f ", t->extra_komi);

	/* Best sequence */
	fprintf(stderr, "| seq ");
	for (int depth = 0; depth < 4; depth++) {
		if (best && best->u.playouts >= 25) {
			fprintf(stderr, "%3s ", coord2sstr(node_coord(best), b));
			best = u->policy->choose(u->policy, best, b, color, resign);
		} else {
			fprintf(stderr, "    ");
		}
	}

	/* Best candidates */
	int nbest = 4;
	float   best_r[nbest];
	coord_t best_c[nbest];
	uct_get_best_moves(t, best_c, best_r, nbest, true);

	fprintf(stderr, "| can %c ", color == S_BLACK ? 'b' : 'w');
	for (int i = 0; i < nbest; i++)
		if (!is_pass(best_c[i]))
			fprintf(stderr, "%3s(%.1f) ", coord2sstr(best_c[i], b), 100 * best_r[i]);
		else
			fprintf(stderr, "          ");

	/* Tree memory usage */
	if (UDEBUGL(3))
		fprintf(stderr, " | %.1fMb", (float)t->nodes_size / 1024 / 1024);
	
	fprintf(stderr, "\n");
}

```



### uct_search_stop

```c
//停止搜索
struct uct_thread_ctx *
uct_search_stop(void)
{
    //assert的作用是先计算表达式 expression ，如果其值为假（即为0），那么它先向stderr打印一条出错信息，然后通过调用 abort 来终止程序运行
	assert(thread_manager_running);

	/* Signal thread manager to stop the workers. */
    /*通知线程管理器停止工作。*/
	pthread_mutex_lock(&finish_mutex); //获取finish_thread锁
	finish_thread = -1;//停止搜索标志
	pthread_cond_signal(&finish_cond);//发送量
	pthread_mutex_unlock(&finish_mutex);//解锁

	/* Collect the thread manager. */
    /*收集线程管理器*/
	struct uct_thread_ctx *pctx;
	thread_manager_running = false;
	pthread_join(thread_manager, (void **) &pctx);
	return pctx;
}
```

### board_setup and board_init

```c
static void
board_setup(struct board *b)
{
	memset(b, 0, sizeof(*b));
    //初始值为－１，且没有颜色
	struct move m = { pass, S_NONE };
	b->last_move = b->last_move2 = b->last_move3 = b->last_move4 = b->last_ko = b->ko = m;
}

struct board *
board_init(char *fbookfile)
{
	struct board *b = malloc2(sizeof(struct board));
	board_setup(b);

	b->fbookfile = fbookfile;

	// Default setup
	b->size = 9 + 2;
	board_clear(b);

	return b;
}

```



### tree_setup_node

```c
/* Initialize a node at a given place in memory.
 * This function may be called by multiple threads in parallel. */
/*在内存中的给定位置初始化节点。此函数可以由多个线程并行调用。*/
static void
tree_setup_node(struct tree *t, struct tree_node *n, coord_t coord, int depth)
{
	static volatile unsigned int hash = 0;
	n->coord = coord;//节点在棋盘的位置
	n->depth = depth;//节点深度
	/* n->hash is used only for debugging. It is very likely (but not
	 * guaranteed) to be unique. */
    /*n->hash仅用于调试。它很可能（但不能保证）是独一无二的*/
	hash_t h = n - (struct tree_node *)0;
	n->hash = (h << 32) + (hash++ & 0xffffffff);
	if (depth > t->max_depth)
		t->max_depth = depth;
}
```

### tree_expand_node

```c

/* Tree symmetry: When possible, we will localize the tree to a single part
 * of the board in tree_expand_node() and possibly flip along symmetry axes
 * to another part of the board in tree_promote_at(). We follow b->symmetry
 * guidelines here. */
/*树对称：如果可能，我们将把树定位到树中板的一个单独部分_expand_node（），并可能沿着对称轴翻转到树中板的另一个部分_promote_at（）。我们在这里遵循b->symmetryguidelines。*/

/* This function must be thread safe, given that board b is only modified by the calling thread. */
/*这个函数必须是线程安全的，因为B板只被调用线程修改。*/
void
tree_expand_node(struct tree *t, struct tree_node *node, struct board *b, enum stone color, struct uct *u, int parity)
{
	/* Get a Common Fate Graph distance map from parent node. */
    /*从父节点获取一个公共的命运图距离图。*/
	int distances[board_size2(b)];
    //判断是不是－１　或者是－２　不是第一步第二步
	if (!is_pass(b->last_move.coord) && !is_resign(b->last_move.coord)) {
		cfg_distances(b, node_coord(node), distances, TREE_NODE_D_MAX);
	} else {
		// Pass or resign - everything is too far.
        //通过或辞职-一切都太远了。
        /*
         #define foreach_point(board_) \
	do { \
		coord_t c = 0; \
		for (; c < board_size(board_) * board_size(board_); c++)

    #define foreach_point_end \
	    } while (0)

         */
        //初始化每个位置的值
		foreach_point(b) { distances[c] = TREE_NODE_D_MAX + 1; } foreach_point_end;
	}

	/* Get a map of prior values to initialize the new nodes with. */
    /*获取先前值的映射以初始化新节点。*/
	struct prior_map map = {
		.b = b,
		.to_play = color,
		.parity = tree_parity(t, parity),
		.distances = distances,
	};
	// Include pass in the prior map.
    //在上一个地图中包括通行证。
	struct move_stats map_prior[board_size2(b) + 1]; map.prior = &map_prior[1];
	bool map_consider[board_size2(b) + 1]; map.consider = &map_consider[1];
	memset(map_prior, 0, sizeof(map_prior));
	memset(map_consider, 0, sizeof(map_consider));
	map.consider[pass] = true;
	int child_count = 1; // for pass
    //计算可以落子的点，有几个就计算几次
	foreach_free_point(b) {
		assert(board_at(b, c) == S_NONE);
		if (!board_is_valid_play_no_suicide(b, color, c))
			continue;
		map.consider[c] = true;
		child_count++;//统计有几个空闲的位置
	} foreach_free_point_end;
	uct_prior(u, node, &map);

	/* Now, create the nodes (all at once if fast_alloc) */
    /*现在，创建节点（如果快速分配，则一次创建所有节点）*/
	struct tree_node *ni = t->nodes ? tree_alloc_node(t, child_count, true) : tree_alloc_node(t, 1, false);
	/* In fast_alloc mode we might temporarily run out of nodes but this should be rare. */
    /*在fast-alloc模式下，我们可能会暂时耗尽节点，但这种情况应该很少发生。*/
	if (!ni) {
		node->is_expanded = false;
		return;
	}
    //ni是我们的第一个节点，　第一个节点没有位置
	tree_setup_node(t, ni, pass, node->depth + 1);

	struct tree_node *first_child = ni;
	ni->parent = node;
    //他的走法是pass
	ni->prior = map.prior[pass]; ni->d = TREE_NODE_D_MAX + 1;

	/* The loop considers only the symmetry playground. */
    /*环只考虑对称运动场。*/
	if (UDEBUGL(6)) {
		fprintf(stderr, "expanding %s within [%d,%d],[%d,%d] %d-%d\n",
				coord2sstr(node_coord(node), b),
				b->symmetry.x1, b->symmetry.y1,
				b->symmetry.x2, b->symmetry.y2,
				b->symmetry.type, b->symmetry.d);
	}
	int child = 1;
	for (int j = b->symmetry.y1; j <= b->symmetry.y2; j++) {
		for (int i = b->symmetry.x1; i <= b->symmetry.x2; i++) {
			if (b->symmetry.d) {
				int x = b->symmetry.type == SYM_DIAG_DOWN ? board_size(b) - 1 - i : i;
				if (x > j) {
					if (UDEBUGL(7))
						fprintf(stderr, "drop %d,%d\n", i, j);
					continue;
				}
			}
            //映射转换位置，将ｉ，ｊ换算成ｃ值
			coord_t c = coord_xy(t->board, i, j);
			if (!map.consider[c]) // Filter out invalid moves 筛选出无效移动
				continue;
			assert(c != node_coord(node)); // I have spotted "C3 C3" in some sequence...我发现“c3 c3”有一些序列…

			struct tree_node *nj = t->nodes ? first_child + child++ : tree_alloc_node(t, 1, false);
            //设置节点，位置和深度
			tree_setup_node(t, nj, c, node->depth + 1);
            //串成一个串　
			nj->parent = node; ni->sibling = nj; ni = nj;

			ni->prior = map.prior[c];
			ni->d = distances[c];
		}
	}
    //链接起这个串
	node->children = first_child; // must be done at the end to avoid race　必须在比赛结束时进行以避免比赛
}


```



### policy_ucb1_init

```c
//ｕｃｂ１策略初始化
struct uct_policy *
policy_ucb1_init(struct uct *u, char *arg)
{
	struct uct_policy *p = calloc2(1, sizeof(*p));
	struct ucb1_policy *b = calloc2(1, sizeof(*b));
	p->uct = u;
	p->data = b;
	p->done = ucb1_done;
	p->descend = ucb1_descend;//下沉
	p->choose = uctp_generic_choose;//
	p->update = ucb1_update;//跟新

	b->explore_p = 0.2;
	b->fpu = 1.1; //INFINITY;

	if (arg) {
		char *optspec, *next = arg;
		while (*next) {
			optspec = next;
			next += strcspn(next, ":");
			if (*next) { *next++ = 0; } else { *next = 0; }

			char *optname = optspec;
			char *optval = strchr(optspec, '=');
			if (optval) *optval++ = 0;

			if (!strcasecmp(optname, "explore_p") && optval) {
				b->explore_p = atof(optval);
			} else if (!strcasecmp(optname, "fpu") && optval) {
				b->fpu = atof(optval);
			} else
				die("ucb1: Invalid policy argument %s or missing value\n", optname);
		}
	}

	return p;
}
```

### slave_loop 主机线程

```c
/* Main loop of a slave thread.
 * Send the current command to the slave machine and wait for a reply.
 * Resend command history if the slave machine is out of sync.
 * Returns when the connection with the slave machine is cut.
 * slave_lock is held on both entry and exit of this function. */
/*从线程的主循环。将当前命令发送到从属计算机并等待答复。如果从机不同步，则重新发送命令历史记录。当与从机的连接被切断时返回。从锁在该功能的入口和出口都保持不变。*/
static void
slave_loop(FILE *f, char *reply_buf, struct slave_state *sstate, bool resend)
{
	char *to_send;
	int last_cmd_count = 0;
	int last_reply_id = -1;
	int reply_slot = -1;
    /*这个是循环等待命令，也就是一直等着是否有命令*/
	for (;;) {
		if (resend) {
			/* Resend complete or partial history */
            /*重新发送完整或部分历史记录，处理失败的情况　断线回复功能*/
			to_send = next_command(last_reply_id);
		} else {
			/* Wait for a new command. */
            /*等待新命令。*/
			while (last_cmd_count == cmd_count)
				pthread_cond_wait(&cmd_cond, &slave_lock);//条件等待，　产生一条命令就处理
			to_send = gtp_cmd;//待发送的命令,在另一个里面，gtp_cmd是要后移的
		}

		/* Command available, send it to slave machine.
		 * If slave was out of sync, send the history.
		 * But first get binary arguments if necessary. */
        /*命令可用，发送到从机。如果slave不同步，发送历史记录。但是如果需要，首先获取二进制参数。*/
		int bin_size = 0;
		void *bin_buf = get_binary_arg(sstate, gtp_cmd,
					       gtp_cmds + CMDS_SIZE - gtp_cmd,
					       &bin_size);
		/* Check that the command is still valid. */
        /*检查命令是否仍然有效。*/
		resend = true;
		if (!bin_buf) continue;

		/* Send the command and get the reply, which always ends with \n\n
		 * The slave machine sends "=id reply" or "?id reply"
		 * with id == cmd_id if it is in sync. */
        /*发送命令并获得答复，该答复始终以\n \n从机发送“=id reply”或“”结尾。id reply“如果它是同步的，id==cmd_id。*/
		last_cmd_count = cmd_count;
		char buf[CMDS_SIZE];
        //发送命令
		int reply_id = send_command(to_send, bin_buf, &bin_size, f,
					    sstate, buf);
		if (reply_id == -1) return;
        //获得回复
		resend = process_reply(reply_id, buf, reply_buf, bin_buf, bin_size,
				       &last_reply_id, &reply_slot, sstate);
	}
}

```

### open_gtp_connection

```c
/* Open the gtp connection on the given port, redirect stdin & stdout to it. */
/*打开给定端口上的GTP连接，将stdin和stdout重定向到该端口。*/

void
open_gtp_connection(int *socket, char *port)
{
	static struct port_info gtp_info = { .socket = -1 };
	gtp_info.port = port;
	int gtp_conn = open_connection(&gtp_info);
    //端口重映射，输入输出，报错等
	for (int d = STDIN; d <= STDOUT; d++) {
		if (dup2(gtp_conn, d) < 0)
			fail("dup2");
	}
	if (DEBUGL(0))
		fprintf(stderr, "gtp connection opened\n");
}
```

### open_connection

```c
/* Open a connection on the given socket/port.
 * Act as server if the port doesn't contain a hostname,
 * as a client otherwise. If socket < 0 or in client mode,
 * create the socket from the given port and update socket.
 * Block until the connection succeeds.
 * Return a file descriptor for the new connection. */
/*在给定的套接字/端口上打开连接。如果端口不包含主机名，则充当服务器，否则充当客户机。如果socket<0或处于客户机模式，则从给定端口创建socket并更新socket。阻止，直到连接成功。返回新连接的文件描述符。*/
static int
open_connection(struct port_info *info)
{
	int conn;
    //ｐ为主机名
	char *p = strchr(info->port, ':');
	if (p) {
		for (int try = 1;; ) {
            //构建链接　充当客户机
			conn = open_client_connection(info->port);
            //每次睡眠的时间会扩大１秒，直到链接成功，为止，直接跳出
			if (conn >= 0) break;
			sleep(try);
			if (try < MAX_WAIT) try++;
		}
		info->socket = conn;
	} else {
        //服务器模式，
		if (info->socket < 0)
			info->socket = port_listen(info->port, MAX_CONNEXIONS);
        //listen() 只是让套接字进入监听状态，并没有真正接收客户端请求，listen() 后面的代码会继续执行，直到遇到 accept()。accept() 会阻塞程序执行（后面代码不能被执行），直到有新的请求到来。
		conn = open_server_connection(info->socket, NULL);
	}
	return conn;
}

```

### open_client_connection

```c

/* Opens a new connection to the given port name, which must
 * contain a host name. Returns the open file descriptor,
 * or -1 if the open fails. */
/*打开与给定端口名的新连接，该端口名必须包含主机名。返回打开的文件描述符，如果打开失败则返回-1。*/
static int
open_client_connection(char *port_name)
{
	char hostname[BSIZE];
	strncpy(hostname, port_name, sizeof(hostname));
	char *port = strchr(hostname, ':');
	assert(port);
	*port++ = '\0';

	struct hostent *host = gethostbyname(hostname);
	if (!host)
		return -1;
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1)
		fail("socket");
	struct sockaddr_in sin;
	memcpy(&sin.sin_addr.s_addr, host->h_addr, host->h_length);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(atoi(port));

	if (connect(sock, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
		close(sock);
		return -1;
	}
	return sock;
}

```

### port_listen

````c
/* Create a socket, bind to it on the given port and listen.
 * This function is restricted to server mode (port has
 * no hostname). Returns the socket. */
/*创建一个套接字，在给定的端口上绑定到它并监听。此功能仅限于服务器模式（端口没有主机名）。返回套接字。*/

int
port_listen(char *port, int max_connections)
{
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1)
		fail("socket");

	struct sockaddr_in server_addr;
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;         
	server_addr.sin_port = htons(atoi(port));     
	server_addr.sin_addr.s_addr = INADDR_ANY; 

	const char val = 1;
	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val)))
		fail("setsockopt");
	if (bind(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1)
		fail("bind");
	if (listen(sock, max_connections) == -1)
		fail("listen");
	return sock;
}
````

### open_server_connection

```c
/* Waits for a connection on the given socket, and returns the file descriptor.
 * Updates the client address if it is not null.
 * WARNING: the connection is not authenticated. As a weak security measure,
 * the connections are limited to a private network. */
/*等待给定套接字上的连接，如果文件描述符不为空，则返回更新客户端地址的文件描述符。
 * 警告：连接未通过身份验证。作为一项薄弱的安全措施，
 * 连接仅限于专用网络。*/
int
open_server_connection(int socket, struct in_addr *client)
{
	assert(socket >= 0);
	for (;;) {
		struct sockaddr_in client_addr;
		int sin_size = sizeof(struct sockaddr_in);
		int fd = accept(socket, (struct sockaddr *)&client_addr, (socklen_t *)&sin_size);
        //accept会阻塞程序执行，直到有新的一个请求到来
		if (fd == -1) {
			fail("accept");
		}
		if (is_private(&client_addr.sin_addr)) {
			if (client)
				*client = client_addr.sin_addr;
			return fd;
		}
		close(fd);
	}
}
```



### send_command

```c
/* Send the gtp command to_send and get a reply from the slave machine.
 * Write the reply in buf which must have at least CMDS_SIZE bytes.
 * If *bin_size > 0, send bin_buf after the gtp command.
 * Return any binary reply in bin_buf and set its size in bin_size.
 * bin_buf is private to the slave and need not be copied.
 * Return the gtp command id, or -1 if error.
 * slave_lock is held on both entry and exit of this function. */
/*将gtp命令发送到send，并从从属计算机获得答复。以buf格式写入答复，其中必须至少包含cmds_-size字节。如果*bin_-size>0，则在gtp命令之后发送bin_-buf。返回bin_buf中的任何二进制回复，并将其大小设置为bin_size。bin_buf对从属服务器是私有的，不需要复制。返回gtp命令ID，如果在该函数的入口和出口上都持有error.slave_锁，则返回-1。*/
static int
send_command(char *to_send, void *bin_buf, int *bin_size,
	     FILE *f, struct slave_state *sstate, char *buf)
{
	assert(to_send && gtp_cmd && bin_buf && bin_size);
	strncpy(buf, to_send, CMDS_SIZE);
	bool resend = to_send != gtp_cmd;

	pthread_mutex_unlock(&slave_lock);

	if (DEBUGL(1) && resend)
		logline(&sstate->client, "? ",
			to_send == gtp_cmds ? "resend all\n" : "partial resend\n");

	double start = time_now();
	fputs(buf, f);

	if (*bin_size)
		fwrite(bin_buf, 1, *bin_size, f);
	fflush(f);

	if (DEBUGV(strchr(buf, '@'), 2)) {
		double ms = (time_now() - start) * 1000.0;
		if (!DEBUGL(3)) {
			char *s = strchr(buf, '\n');
			if (s) s[1] = '\0';
		}
		logline(&sstate->client, ">>", buf);
		if (*bin_size) {
			char b[1024];
			snprintf(b, sizeof(b),
				 "sent cmd %d+%d bytes in %.4fms\n",
				 (int)strlen(buf), *bin_size, ms);
			logline(&sstate->client, "= ", b);
		}
	}

	/* Reuse the buffers for the reply. */
    /*重复使用回复缓冲区。*/
	*bin_size = sstate->max_buf_size;
	int reply_id = get_reply(f, sstate->client, buf, bin_buf, bin_size);

	pthread_mutex_lock(&slave_lock);
	return reply_id;
}

```

### gtp_parse

````c
/* XXX: THIS IS TOTALLY INSECURE!!!!
 * Even basic input checking is missing. */

enum parse_code
gtp_parse(struct board *board, struct engine *engine, struct time_info *ti, char *buf)
{
	if (strchr(buf, '#'))
		*strchr(buf, '#') = 0;

	gtp_t gtp_struct = { .next = buf, .id = -1 };
	gtp_t *gtp = &gtp_struct;
    //cmd就指向第一段命令的
	next_tok(gtp->cmd);
    //跳过数字
	if (isdigit(*gtp->cmd)) {
		gtp->id = atoi(gtp->cmd);
		next_tok(gtp->cmd);
	}
    //并且不为空
	if (!*gtp->cmd)
		return P_OK;
    //判断当前引擎是否有和这个函数 和这个命令是否有效
	if (engine->notify && gtp_is_valid(engine, gtp->cmd)) {
		char *reply;
		enum parse_code c = engine->notify(engine, board, gtp->id, gtp->cmd, gtp->next, &reply);
		if (c == P_NOREPLY) {
			gtp->id = NO_REPLY;
		} else if (c == P_DONE_OK) {
			gtp_reply(gtp, reply, NULL);
			return P_OK;
		} else if (c == P_DONE_ERROR) {
			gtp_error(gtp, reply, NULL);
			/* This is an internal error for the engine, but
			 * it is still OK from main's point of view. */
            /*这是发动机的一个内部错误，但从MAIN的角度来看仍然可以。*/
			return P_OK;
		} else if (c != P_OK) {
			return c;
		}
	}
    //commands 是一个静态结构体数组，分别是命令和命令执行的函数
	for (int i = 0; commands[i].cmd; i++)
        //匹配命令
		if (!strcasecmp(gtp->cmd, commands[i].cmd)) {
            //执行命令匹配函数
			enum parse_code ret = commands[i].f(board, engine, ti, gtp);
			/* For functions convenience: no reply means empty reply */
            /*为方便功能：无应答表示空应答*/
			if (!gtp->replied)
				gtp_reply(gtp, NULL);
			return ret;
		}
	
	gtp_error(gtp, "unknown command", NULL);
	return P_UNKNOWN_COMMAND;

````

### distributed_notify

```c

/* Dispatch a new gtp command to all slaves.
 * The slave lock must not be held upon entry and is released upon return.
 * args is empty or ends with '\n' */
/*向所有从系统发送一个新的gtp命令。从系统锁不能在进入时保持，返回时释放。参数为空或以'\n'结尾。*/
static enum parse_code
distributed_notify(struct engine *e, struct board *b, int id, char *cmd, char *args, char **reply)
{
	struct distributed *dist = e->data;

	/* Commands that should not be sent to slaves.
	 * time_left will be part of next pachi-genmoves,
	 * we reduce latency by not forwarding it here. */
    /*不应该发送到从系统的命令。离开的时间将是下一个pachi genmoves的一部分，我们不在这里转发它来减少延迟。*/
	//当是这些命令的话，直接返回，　用原来的方式方法
    if ((!strcasecmp(cmd, "quit") && !dist->slaves_quit) //等于这些命令直接返回ok
	    || !strcasecmp(cmd, "pachi-gentbook")
	    || !strcasecmp(cmd, "pachi-dumptbook")
	    || !strcasecmp(cmd, "kgs-chat")
	    || !strcasecmp(cmd, "time_left")

	    /* and commands that will be sent to slaves later */
	    || !strcasecmp(cmd, "genmove")
	    || !strcasecmp(cmd, "kgs-genmove_cleanup")
	    || !strcasecmp(cmd, "final_score")
	    || !strcasecmp(cmd, "final_status_list"))
		return P_OK;
    //协议同步锁，里面是获取从机锁　如果所有线程都运行到等待的状态，是解锁状态
	protocol_lock();//没有这个命令的话执行到这里

	// Create a new command to be sent by the slave threads.
    //创建一个由从属线程发送的新命令。
	new_cmd(b, cmd, args);

	/* Wait for replies here. If we don't wait, we run the
	 * risk of getting out of sync with most slaves and
	 * sending command history too frequently. But don't wait
	 * for all slaves otherwise we can lose on time because of
	 * a single slow slave when replaying a whole game. */
	int min_slaves = active_slaves > 1 ? 3 * active_slaves / 4 : 1;
	get_replies(time_now() + MAX_FAST_CMD_WAIT, min_slaves);

	protocol_unlock();

	// At the beginning wait even more for late slaves.
	if (b->moves == 0) sleep(1);
	return P_OK;
}

```



### new_cmd

```c
/* Update the command history, then create a new gtp command
 * for all slaves. The slave lock is held upon entry and
 * upon return, so the command will actually be sent when the
 * lock is released. cmd is a single word; args has all
 * arguments and is empty or has a trailing \n */
/*更新命令历史记录，然后为所有从系统创建一个新的gtp命令。从锁在进入和返回时保持不变，因此在释放锁时实际上会发送命令。cmd是一个单字；args有所有参数，为空或有一个尾随的\n*/
void
new_cmd(struct board *b, char *cmd, char *args)
{
	// Clear the history when a new game starts:
    // gtp_cmd初始值为空的静态指针，gtp_cmds静态指针数组
	if (!gtp_cmd || is_gamestart(cmd)) { //初始化命令
		gtp_cmd = gtp_cmds;// 字符数组，gtp_cmds里面存储命令　gtp_cmd是指向字符数组的首位
		memset(history, 0, sizeof(history)); //历史命令的数组
	} else {
		/* Preserve command history for new slaves.
		 * To indicate that the slave should only reply to
		 * the last command we force the id of previous
		 * commands to be just the move number. */
        /*保留新奴隶的命令历史记录。为了指示从系统只应回复上一个命令，我们强制先前命令的ID仅为移动编号。*/
		int id = prevent_reply(atoi(gtp_cmd));//
		int len = strspn(gtp_cmd, "0123456789");
        /*
返回字符串 str 开头连续包含字符串 accept 内的字符数目。所以，如果 str 所包含的字符都属于 accept，那么返回 str 的长度；如果 str 的第一个字符不属于 accept，那么返回 0。*/
		char buf[32];
		snprintf(buf, sizeof(buf), "%0*d", len, id);//向字符数组中输出字符串，len是输出的长度后面是输出的内容，是命令的头部id
		memcpy(gtp_cmd, buf, len);
        //一个ｉｄ存入，　指向空位
		gtp_cmd += strlen(gtp_cmd);//让gtp指向最后
	}

	// Let the slave threads send the new gtp command:
    //让从属线程发送新的gtp命令：
	update_cmd(b, cmd, args, true);
}

```

### update_cmd

```c

/* Create a new gtp command for all slaves. The slave lock is held
 * upon entry and upon return, so the command will actually be
 * sent when the lock is released. The last command is overwritten
 * if gtp_cmd points to a non-empty string. cmd is a single word;
 * args has all arguments and is empty or has a trailing \n */
/*为所有从系统创建一个新的gtp命令。从锁在进入和返回时保持不变，因此在释放锁时实际上会发送命令。如果gtp_cmd指向非空字符串，则最后一个命令将被覆盖。cmd是一个单字；args有所有参数，为空或有一个尾随的\n*/
void
update_cmd(struct board *b, char *cmd, char *args, bool new_id)
{
	assert(gtp_cmd);
	/* To make sure the slaves are in sync, we ignore the original id
	 * and use the board number plus some random bits as gtp id. */
    /*为了确保从机是同步的，我们忽略了原始ID，并使用板号加上一些随机位作为GTP ID.*/
	static int gtp_id = -1;
	int moves = is_reset(cmd) ? 0 : b->moves;//
	if (new_id) {//如果他是一个新的ｉｄ
		int prev_id = gtp_id;
		do {
			/* fast_random() is 16-bit only so the multiplication can't overflow. */
            /*fast_random（）只有16位，所以乘法不能溢出。*/
            //保证上下两个进程的ｉｄ不一样，同一步内
			gtp_id = force_reply(moves + fast_random(65535) * DIST_GAMELEN); //获取熬一个新的gtp id，如果前后两个一样，在做一次，知道他俩不一样，为啥要随机，
		} while (gtp_id == prev_id);//为啥要随机 fast_random返回的是一个随机数，游戏的最大长度，move 是步数
		reply_count = 0;
	}
    //这个时间才把命令写进去
	snprintf(gtp_cmd, gtp_cmds + CMDS_SIZE - gtp_cmd, "%d %s %s",
		 gtp_id, cmd, *args ? args : "\n");
	cmd_count++;

	/* Remember history for out-of-sync slaves. */
    /*记住不同步从服务器的历史记录。*/
	static int slot = 0;
	static struct cmd_history *last = NULL;
	if (new_id) {
		if (last) last->next_cmd = gtp_cmd;
		slot = (slot + 1) % MAX_CMDS_PER_MOVE;
		last = &history[moves][slot];//如果这是一个新的命令存起来
		last->gtp_id = gtp_id;
		last->next_cmd = NULL;
	}
	// Notify the slave threads about the new command.
    //通知从线程有关新命令的信息。
	pthread_cond_broadcast(&cmd_cond);//条件信号的广播　但是还没有解锁
}

```



## 命令

### genmove b

### board size

### play B4的时候干了啥



## 核心算法

### UCB问题

//ucb问题，多臂老虎机问题，得知某个把手，被游戏的次数越少，玩他的概率越高，她赢得概率越高，他被玩的概率越高

### UCT

解决多臂老虎机的算法





## 问题记录

1.在board.h中 250行hash_t的作用是啥

2.FB_ONLY的定义，有两种，作用分别是啥

3.search.c　250 行左右　，这两行可以交换嘛

```c
  //两个线程并行执行
	pthread_create(&thread_manager, NULL, spawn_thread_manager, s->ctx);
	thread_manager_running = true;//不能进行交换
```

4.什么情况下线程ｉｄ小于０　　ｓｅａｒｃｈ.c

　　finish_thread

//在uct_search_stop函数内部

5.树的裁剪

6.垃圾回收

7.virtual_lost的值是几？

在uct_playout里面

8.为什么将gtp_cmd存入局部变量里，在slave_loop　里面

因为gtp_cmd变量在主线程里面会后移，位置就变了



9.处理回复怎么处理多个从同时给了我们回复我们不会乱　在slave_loop里面的process_reply

10.发送命令为什么需要一个局部变量数组slave_loop

11.有新的引擎突然加入怎么算，说以分布式引擎里面一定有存储历史命令的东西

## 各种故事线

1.随机下棋的线　一次完整的蒙特卡洛搜索

2.分布式引擎线路





## 分布式系统

一个系统中的任何一个电脑都能成为主机