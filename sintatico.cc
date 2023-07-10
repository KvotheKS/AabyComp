// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.





#include "sintatico.hh"


// Unqualified %code blocks.
#line 19 "analise/sintatico.yy"

        # define YY_DECL \
        yy::parser::symbol_type yylex ()
        
        YY_DECL;
        std::unordered_map<std::string,int> symTable;
        int semanticErrors = 0;
        int syntaticError = 0;
        int branchcount = 0;
        std::string currentChain = "0";
        //std::ofstream _file("o.txt");
        std::string _f_out;
        extern std::string __immediate;

#line 61 "sintatico.cc"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif



// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

namespace yy {
#line 134 "sintatico.cc"

  /// Build a parser object.
  parser::parser ()
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr)
#else

#endif
  {}

  parser::~parser ()
  {}

  parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/



  // by_state.
  parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  parser::symbol_kind_type
  parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  parser::stack_symbol_type::stack_symbol_type ()
  {}

  parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_command_seq: // command_seq
      case symbol_kind::S_command: // command
      case symbol_kind::S_if_loop: // if_loop
      case symbol_kind::S_exp: // exp
      case symbol_kind::S_fst_exp: // fst_exp
      case symbol_kind::S_sec_exp: // sec_exp
      case symbol_kind::S_thr_exp: // thr_exp
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s)
  {
    switch (that.kind ())
    {
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_command_seq: // command_seq
      case symbol_kind::S_command: // command
      case symbol_kind::S_if_loop: // if_loop
      case symbol_kind::S_exp: // exp
      case symbol_kind::S_fst_exp: // fst_exp
      case symbol_kind::S_sec_exp: // sec_exp
      case symbol_kind::S_thr_exp: // thr_exp
        value.move< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_command_seq: // command_seq
      case symbol_kind::S_command: // command
      case symbol_kind::S_if_loop: // if_loop
      case symbol_kind::S_exp: // exp
      case symbol_kind::S_fst_exp: // fst_exp
      case symbol_kind::S_sec_exp: // sec_exp
      case symbol_kind::S_thr_exp: // thr_exp
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    return *this;
  }

  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_command_seq: // command_seq
      case symbol_kind::S_command: // command
      case symbol_kind::S_if_loop: // if_loop
      case symbol_kind::S_exp: // exp
      case symbol_kind::S_fst_exp: // fst_exp
      case symbol_kind::S_sec_exp: // sec_exp
      case symbol_kind::S_thr_exp: // thr_exp
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " (";
        YY_USE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  parser::yypop_ (int n) YY_NOEXCEPT
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  parser::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  parser::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::operator() ()
  {
    return parse ();
  }

  int
  parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex ());
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_command_seq: // command_seq
      case symbol_kind::S_command: // command
      case symbol_kind::S_if_loop: // if_loop
      case symbol_kind::S_exp: // exp
      case symbol_kind::S_fst_exp: // fst_exp
      case symbol_kind::S_sec_exp: // sec_exp
      case symbol_kind::S_thr_exp: // thr_exp
        yylhs.value.emplace< std::string > ();
        break;

      default:
        break;
    }



      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // program: LET declarations IN command_seq END
#line 69 "analise/sintatico.yy"
                                             { 
        _f_out = programheader() + yystack_[1].value.as < std::string > () + exitprogram(symTable); 
}
#line 572 "sintatico.cc"
    break;

  case 4: // declarations: INTEGER id_seq IDENTIFIER '.'
#line 75 "analise/sintatico.yy"
                                        {
                std::string name = yystack_[1].value.as < std::string > ();
                std::unordered_map<std::string,int>::iterator tracer = symTable.find(name);
                if (tracer != symTable.end()) {
                        // Variável já declarada, erro.
                        std::cout << "Variable with same name already declared: " << name << "\n";
                        semanticErrors++;
                } else {
                        std::cout << "New variable: " << name << "\n";
                        symTable.emplace(name,symTable.size());
                }
        }
#line 589 "sintatico.cc"
    break;

  case 6: // id_seq: id_seq IDENTIFIER ','
#line 90 "analise/sintatico.yy"
                                {
                        std::string name = yystack_[1].value.as < std::string > ();
                        std::unordered_map<std::string,int>::iterator tracer = symTable.find(name);
                        if (tracer != symTable.end()) {
                                // Variável já declarada, erro.
                                std::cout << "Variable with same name already declared: " << name << "\n";
                                semanticErrors++;
                        } else {
                                std::cout << "New variable: " << name << "\n";
                                symTable.emplace(name,symTable.size());
                        }
                }
#line 606 "sintatico.cc"
    break;

  case 7: // command_seq: %empty
#line 104 "analise/sintatico.yy"
             {yylhs.value.as < std::string > () = "";}
#line 612 "sintatico.cc"
    break;

  case 8: // command_seq: command_seq command ';'
#line 105 "analise/sintatico.yy"
                                  {yylhs.value.as < std::string > () = yystack_[2].value.as < std::string > () + yystack_[1].value.as < std::string > ();}
#line 618 "sintatico.cc"
    break;

  case 9: // command: SKIP
#line 108 "analise/sintatico.yy"
              {yylhs.value.as < std::string > () = "";}
#line 624 "sintatico.cc"
    break;

  case 10: // command: READ IDENTIFIER
#line 109 "analise/sintatico.yy"
                            {
                std::string name = yystack_[0].value.as < std::string > ();
                std::unordered_map<std::string,int>::iterator tracer = symTable.find(name);
                if (tracer == symTable.end()) {
                        // Variável não declarada, erro.
                        std::cout << "Variable not declared: " << name << "\n";
                        semanticErrors++;
                }
                if(!semanticErrors)
                        yylhs.value.as < std::string > () = readcall(symTable, yystack_[0].value.as < std::string > ()) + pushstack();
        }
#line 640 "sintatico.cc"
    break;

  case 11: // command: WRITE exp
#line 120 "analise/sintatico.yy"
                    {
                if(!semanticErrors)
                {
                        yylhs.value.as < std::string > () = TraverseExp(symTable, yystack_[0].value.as < std::string > ())  + writecall();
                }
        }
#line 651 "sintatico.cc"
    break;

  case 12: // command: IDENTIFIER ASSGNOP exp
#line 126 "analise/sintatico.yy"
                                    {
                std::string name = yystack_[2].value.as < std::string > ();
                std::unordered_map<std::string,int>::iterator tracer = symTable.find(name);
                if (tracer == symTable.end()) {
                        // Variável não declarada, erro.
                        std::cout << "Variable not declared: " << name << "\n";
                        semanticErrors++;
                }
                if(!semanticErrors)
                {
                        yylhs.value.as < std::string > () = TraverseExp(symTable, yystack_[0].value.as < std::string > ()); 
                        yylhs.value.as < std::string > () += assignvar(symTable, yystack_[2].value.as < std::string > ()) + pop(1);
                }
        }
#line 670 "sintatico.cc"
    break;

  case 13: // command: IF exp THEN command_seq if_loop FI
#line 140 "analise/sintatico.yy"
                                               {
                std::string if_cmd;
                if(!semanticErrors)
                {
                        std::string branchnum = std::to_string(branchcount++);
                        if_cmd = TraverseExp(symTable, yystack_[4].value.as < std::string > ()) + pop(1) +
                        "\tbeq t0, zero, ifout" + branchnum + '\n';
                        
                        if_cmd += yystack_[2].value.as < std::string > () + "\tjal zero, ifchainout" + currentChain + "\nifout" + 
                                  branchnum + ":\n" + yystack_[1].value.as < std::string > () + "ifchainout" + currentChain + ":\n";
                }
                currentChain = std::to_string(branchcount);
                yylhs.value.as < std::string > () = if_cmd;
        }
#line 689 "sintatico.cc"
    break;

  case 14: // command: WHILE exp DO command_seq END
#line 155 "analise/sintatico.yy"
                                       {
                std::string while_cmd;
                if(!semanticErrors)
                {
                        std::string branchnum = std::to_string(branchcount++);
                        while_cmd = "whilecheck" + branchnum + ":\n";
                        while_cmd += TraverseExp(symTable, yystack_[3].value.as < std::string > ()) + pop(1) + 
                        "\tbeq t0, zero, whileout" + branchnum + "\n" + yystack_[1].value.as < std::string > () +
                        "\tjal zero, whilecheck" + branchnum + "\nwhileout" + branchnum + ":\n";
                }

                yylhs.value.as < std::string > () = while_cmd;
        }
#line 707 "sintatico.cc"
    break;

  case 15: // if_loop: %empty
#line 170 "analise/sintatico.yy"
         {yylhs.value.as < std::string > () = "";}
#line 713 "sintatico.cc"
    break;

  case 16: // if_loop: ELIF exp THEN command_seq if_loop
#line 171 "analise/sintatico.yy"
                                            {
                std::string if_cmd;
                std::string branchnum = std::to_string(branchcount++);
                        
                if_cmd = TraverseExp(symTable, yystack_[3].value.as < std::string > ()) + pop(1) +
                "\tbeq t0, zero, ifout" + branchnum + '\n';
                if_cmd += yystack_[1].value.as < std::string > () + "\tjal zero, ifchainout" + currentChain + "\nifout" + 
                                branchnum + ":\n" + yystack_[0].value.as < std::string > ();
                yylhs.value.as < std::string > () = if_cmd;
        }
#line 728 "sintatico.cc"
    break;

  case 17: // if_loop: ELSE command_seq
#line 181 "analise/sintatico.yy"
                           { yylhs.value.as < std::string > () = yystack_[0].value.as < std::string > (); }
#line 734 "sintatico.cc"
    break;

  case 18: // exp: fst_exp '<' fst_exp
#line 184 "analise/sintatico.yy"
                              {yylhs.value.as < std::string > () = "< " + yystack_[2].value.as < std::string > () + " " + yystack_[0].value.as < std::string > () + " "; }
#line 740 "sintatico.cc"
    break;

  case 19: // exp: fst_exp '=' fst_exp
#line 185 "analise/sintatico.yy"
                                {yylhs.value.as < std::string > () = "= " + yystack_[2].value.as < std::string > () + " " + yystack_[0].value.as < std::string > () + " "; }
#line 746 "sintatico.cc"
    break;

  case 20: // exp: fst_exp '>' fst_exp
#line 186 "analise/sintatico.yy"
                                {yylhs.value.as < std::string > () = "> " + yystack_[2].value.as < std::string > () + " " + yystack_[0].value.as < std::string > () + " ";}
#line 752 "sintatico.cc"
    break;

  case 21: // exp: fst_exp
#line 187 "analise/sintatico.yy"
                  {yylhs.value.as < std::string > () = yystack_[0].value.as < std::string > ();}
#line 758 "sintatico.cc"
    break;

  case 22: // fst_exp: sec_exp '+' fst_exp
#line 190 "analise/sintatico.yy"
                             {yylhs.value.as < std::string > () = "+ " + yystack_[2].value.as < std::string > () + " " + yystack_[0].value.as < std::string > () + " ";}
#line 764 "sintatico.cc"
    break;

  case 23: // fst_exp: sec_exp '-' fst_exp
#line 191 "analise/sintatico.yy"
                              {yylhs.value.as < std::string > () = "- " + yystack_[2].value.as < std::string > () + " " + yystack_[0].value.as < std::string > () + " ";}
#line 770 "sintatico.cc"
    break;

  case 24: // fst_exp: sec_exp
#line 192 "analise/sintatico.yy"
                  {yylhs.value.as < std::string > () = yystack_[0].value.as < std::string > ();}
#line 776 "sintatico.cc"
    break;

  case 25: // sec_exp: thr_exp '*' sec_exp
#line 195 "analise/sintatico.yy"
                               {yylhs.value.as < std::string > () = "* " + yystack_[2].value.as < std::string > () + " " + yystack_[0].value.as < std::string > () + " ";}
#line 782 "sintatico.cc"
    break;

  case 26: // sec_exp: thr_exp '/' sec_exp
#line 196 "analise/sintatico.yy"
                                {yylhs.value.as < std::string > () = "/ " + yystack_[2].value.as < std::string > () + " " + yystack_[0].value.as < std::string > () + " ";}
#line 788 "sintatico.cc"
    break;

  case 27: // sec_exp: thr_exp
#line 197 "analise/sintatico.yy"
                  {yylhs.value.as < std::string > () = yystack_[0].value.as < std::string > ();}
#line 794 "sintatico.cc"
    break;

  case 28: // thr_exp: IDENTIFIER
#line 200 "analise/sintatico.yy"
                       {
                std::string name = yystack_[0].value.as < std::string > ();
                std::unordered_map<std::string,int>::iterator tracer = symTable.find(name);
                if (tracer == symTable.end()) {
                        // Variável não declarada, erro.
                        std::cout << "Variable not declared: " << name << "\n";
                        semanticErrors++;
                }
                yylhs.value.as < std::string > () = yystack_[0].value.as < std::string > ();
        }
#line 809 "sintatico.cc"
    break;

  case 29: // thr_exp: NUMBER
#line 210 "analise/sintatico.yy"
                 { yylhs.value.as < std::string > () = __immediate; }
#line 815 "sintatico.cc"
    break;

  case 30: // thr_exp: '(' exp ')'
#line 211 "analise/sintatico.yy"
                      {yylhs.value.as < std::string > () = yystack_[1].value.as < std::string > ();}
#line 821 "sintatico.cc"
    break;


#line 825 "sintatico.cc"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        std::string msg = YY_("syntax error");
        error (YY_MOVE (msg));
      }


    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;


      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.what ());
  }

#if YYDEBUG || 0
  const char *
  parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytname_[yysymbol];
  }
#endif // #if YYDEBUG || 0









  const signed char parser::yypact_ninf_ = -33;

  const signed char parser::yytable_ninf_ = -1;

  const signed char
  parser::yypact_[] =
  {
       3,     6,    14,   -33,    17,   -33,    10,   -33,    19,    11,
     -33,   -33,   -33,     1,   -33,     1,    12,     1,     8,    22,
     -33,   -33,     1,    31,    15,    26,    30,    49,   -33,   -33,
       1,   -33,    34,   -33,     1,     1,     1,     1,     1,     1,
       1,   -33,   -33,   -33,    -3,   -33,   -33,   -33,   -33,   -33,
     -33,   -33,    27,     1,   -33,    58,   -33,    59,    38,   -33,
     -33,    -3,   -33
  };

  const signed char
  parser::yydefact_[] =
  {
       0,     3,     0,     5,     0,     1,     0,     7,     0,     0,
       4,     6,     9,     0,     2,     0,     0,     0,     0,     0,
      29,    28,     0,     0,    21,    24,    27,     0,    10,    11,
       0,     8,     0,     7,     0,     0,     0,     0,     0,     0,
       0,     7,    12,    30,    15,    18,    20,    19,    23,    22,
      25,    26,     0,     0,     7,     0,    14,     0,    17,    13,
       7,    15,    16
  };

  const signed char
  parser::yypgoto_[] =
  {
     -33,   -33,   -33,   -33,   -32,   -33,     7,   -15,    24,    25,
     -33
  };

  const signed char
  parser::yydefgoto_[] =
  {
       0,     2,     4,     6,     9,    19,    55,    23,    24,    25,
      26
  };

  const signed char
  parser::yytable_[] =
  {
      27,    44,    29,    12,    13,    53,     1,    32,    54,    52,
      15,     3,    16,    17,     5,    42,    18,    12,    13,    20,
      21,     7,    58,    14,    15,    30,    16,    17,    61,     8,
      18,    28,    22,    12,    13,    34,    35,    36,    57,    56,
      15,    33,    16,    17,    12,    13,    18,    10,    11,    37,
      38,    15,    31,    16,    17,    39,    40,    18,    45,    46,
      47,    48,    49,    41,    50,    51,    43,    59,    62,    60
  };

  const signed char
  parser::yycheck_[] =
  {
      15,    33,    17,     6,     7,     8,     3,    22,    11,    41,
      13,     5,    15,    16,     0,    30,    19,     6,     7,    18,
      19,     4,    54,    12,    13,    17,    15,    16,    60,    19,
      19,    19,    31,     6,     7,    20,    21,    22,    53,    12,
      13,    10,    15,    16,     6,     7,    19,    28,    29,    23,
      24,    13,    30,    15,    16,    25,    26,    19,    34,    35,
      36,    37,    38,    14,    39,    40,    32,     9,    61,    10
  };

  const signed char
  parser::yystos_[] =
  {
       0,     3,    34,     5,    35,     0,    36,     4,    19,    37,
      28,    29,     6,     7,    12,    13,    15,    16,    19,    38,
      18,    19,    31,    40,    41,    42,    43,    40,    19,    40,
      17,    30,    40,    10,    20,    21,    22,    23,    24,    25,
      26,    14,    40,    32,    37,    41,    41,    41,    41,    41,
      42,    42,    37,     8,    11,    39,    12,    40,    37,     9,
      10,    37,    39
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    33,    34,    35,    35,    36,    36,    37,    37,    38,
      38,    38,    38,    38,    38,    39,    39,    39,    40,    40,
      40,    40,    41,    41,    41,    42,    42,    42,    43,    43,
      43
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     5,     0,     4,     0,     3,     0,     3,     1,
       2,     2,     3,     6,     5,     0,     5,     2,     3,     3,
       3,     1,     3,     3,     1,     3,     3,     1,     1,     1,
       3
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "LET", "IN", "INTEGER",
  "SKIP", "IF", "ELIF", "FI", "THEN", "ELSE", "END", "WHILE", "DO", "READ",
  "WRITE", "ASSGNOP", "NUMBER", "IDENTIFIER", "'<'", "'>'", "'='", "'-'",
  "'+'", "'*'", "'/'", "'^'", "'.'", "','", "';'", "'('", "')'", "$accept",
  "program", "declarations", "id_seq", "command_seq", "command", "if_loop",
  "exp", "fst_exp", "sec_exp", "thr_exp", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const unsigned char
  parser::yyrline_[] =
  {
       0,    69,    69,    74,    75,    89,    90,   104,   105,   108,
     109,   120,   126,   140,   155,   170,   171,   181,   184,   185,
     186,   187,   190,   191,   192,   195,   196,   197,   200,   210,
     211
  };

  void
  parser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  parser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


} // yy
#line 1166 "sintatico.cc"

#line 214 "analise/sintatico.yy"




void yy::parser::error (const std::string& m) /* Called by yyparse on error */
{
        syntaticError++;
	std::cerr << m << '\n';
}
