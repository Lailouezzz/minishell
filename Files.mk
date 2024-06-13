FILES	=																	\
	utils main parser/table parser/prod/prod_rl parser/prod/prod_arg_red	\
	parser/prod/prod_sc parser/prod/prod_arl parser/prod/prod_subshell		\
	parser/prod/prod_sc_free parser/prod/prod_and_or						\
	parser/prod/prod_command_free parser/prod/prod_io_pn					\
	parser/prod/prod_pipeline parser/prod/prod_command parser/ast/subshell	\
	parser/ast/args parser/ast/arg_red parser/ast/command_line				\
	parser/ast/redirect_list parser/ast/args_redirect_list					\
	parser/ast/pipeline parser/ast/command parser/ast/and_or				\
	parser/ast/io_info parser/ast/simple_command							\
	tokenizer/tokenizer_helpers tokenizer/token_gen_table					\
	tokenizer/tokenizer_wildcard tokenizer/tokenizer_initial				\
	tokenizer/lr_token_list tokenizer/tokenize tokenizer/tokenizer_dollar	\
	tokenizer/tokenizer_io_pipe_and_or tokenizer/tokenizer_word				\
	tokenizer/generator/bracket tokenizer/generator/word_io_and_or_pipe_end	\
	tokenizer/generator/free_cb utils/dyn_str utils/ft_count_if				\
	core/env/destroy core/env/init core/env/set core/env/get				\
	core/env/helper core/env/restore_termios core/exec/init					\
	core/exec/sig_handler core/exec/command_runner							\
	core/exec/command_token_executor core/exec/loop core/exec/_utils2		\
	core/exec/command_launcher core/exec/heredoc_sig_handler				\
	core/exec/redirections core/exec/and_or_executor core/exec/cleanup		\
	core/exec/prompt core/exec/create_heredoc core/exec/_utils1				\
	core/exec/pipeline_executor core/exec/exec								\
	core/exec/builtins/builtin_exit core/exec/builtins/builtin_cd			\
	core/exec/builtins/builtin_unset core/exec/builtins/builtin_echo		\
	core/exec/builtins/builtin_env core/exec/builtins/builtins_data			\
	core/exec/builtins/builtin_export core/exec/builtins/builtin_pwd		\
