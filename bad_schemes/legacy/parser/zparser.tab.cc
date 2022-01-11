// A Bison parser, made by GNU Bison 3.5.1.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2020 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

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

// Undocumented macros, especially those whose name start with YY_,
// are private implementation details.  Do not rely on them.


// Take the name prefix into account.
#define yylex   testlex

// First part of user prologue.
#line 3 "zparser.yy"
 /*** C/C++ Declarations ***/

#include <stdio.h>
#include <string>
#include <vector>

#include "../l_zobject.h"
//#include <openabe/utils/zerror.h>
#include "../l_zconstants.h"
#include "../l_zbytestring.h"
#include "../l_zfunctioninput.h"
#include "../l_zinteger.h"
#include "../l_zattributelist.h"
#include "../l_zpolicy.h"


#line 59 "zparser.tab.cc"


#include "zparser.tab.hh"

// Second part of user prologue.
#line 96 "zparser.yy"


#include "l_zdriver.h"
#include "l_zscanner.h"

/* this "connects" the bison parser in the driver to the flex scanner class
 * object. it defines the yylex() function call to pull the next token from the
 * current lexer object of the driver context. */
#undef yylex
#define yylex driver.lexer->lex


#line 78 "zparser.tab.cc"



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

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


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
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

//namespace test {
#line 170 "zparser.tab.cc"


  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              else
                goto append;

            append:
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
  Parser::Parser (class Driver& driver_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      driver (driver_yyarg)
  {}

  Parser::~Parser ()
  {}

  Parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | Symbol types.  |
  `---------------*/

  // basic_symbol.
#if 201103L <= YY_CPLUSPLUS
  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (basic_symbol&& that)
    : Base (std::move (that))
    , value (std::move (that.value))
    , location (std::move (that.location))
  {}
#endif

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value (that.value)
    , location (that.location)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_MOVE_REF (location_type) l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (semantic_type) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  bool
  Parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  void
  Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    value = YY_MOVE (s.value);
    location = YY_MOVE (s.location);
  }

  // by_type.
  Parser::by_type::by_type ()
    : type (empty_symbol)
  {}

#if 201103L <= YY_CPLUSPLUS
  Parser::by_type::by_type (by_type&& that)
    : type (that.type)
  {
    that.clear ();
  }
#endif

  Parser::by_type::by_type (const by_type& that)
    : type (that.type)
  {}

  Parser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  void
  Parser::by_type::clear ()
  {
    type = empty_symbol;
  }

  void
  Parser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  int
  Parser::by_type::type_get () const YY_NOEXCEPT
  {
    return type;
  }


  // by_state.
  Parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  Parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  Parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  Parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  Parser::symbol_number_type
  Parser::by_state::type_get () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[+state];
  }

  Parser::stack_symbol_type::stack_symbol_type ()
  {}

  Parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.value), YY_MOVE (that.location))
  {
#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  Parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.value), YY_MOVE (that.location))
  {
    // that is emptied.
    that.type = empty_symbol;
  }

#if YY_CPLUSPLUS < 201103L
  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    location = that.location;
    return *this;
  }

  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    switch (yysym.type_get ())
    {
      case 4: // "string"
#line 89 "zparser.yy"
                    { delete (yysym.value.stringVal); }
#line 414 "zparser.tab.cc"
        break;

      case 33: // number
#line 92 "zparser.yy"
                    { delete (yysym.value.uInteger); }
#line 420 "zparser.tab.cc"
        break;

      case 34: // policy
#line 90 "zparser.yy"
                    { delete (yysym.value.treeNode); }
#line 426 "zparser.tab.cc"
        break;

      case 35: // attrlist
#line 91 "zparser.yy"
                    { delete (yysym.value.oabeAttrList); }
#line 432 "zparser.tab.cc"
        break;

      default:
        break;
    }
  }

#if YYDEBUG
  template <typename Base>
  void
  Parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
#if defined __GNUC__ && ! defined __clang__ && ! defined __ICC && __GNUC__ * 100 + __GNUC_MINOR__ <= 408
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
#endif
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  void
  Parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  Parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  Parser::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  Parser::state_type
  Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  bool
  Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Parser::operator() ()
  {
    return parse ();
  }

  int
  Parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    // User initialization code.
#line 47 "zparser.yy"
{
    // initialize the initial location object
    yyla.location.begin.filename = yyla.location.end.filename = &driver.streamname;
}

#line 577 "zparser.tab.cc"


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
        YYCDEBUG << "Reading a token: ";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            yyla.type = yytranslate_ (yylex (&yyla.value, &yyla.location));
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

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
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
      /* If YYLEN is nonzero, implement the default value of the
         action: '$$ = $1'.  Otherwise, use the top of the stack.

         Otherwise, the following line sets YYLHS.VALUE to garbage.
         This behavior is undocumented and Bison users should not rely
         upon it.  */
      if (yylen)
        yylhs.value = yystack_[yylen - 1].value;
      else
        yylhs.value = yystack_[0].value;

      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2:
#line 114 "zparser.yy"
                       { driver.set_policy((yystack_[0].value.treeNode)); }
#line 704 "zparser.tab.cc"
    break;

  case 3:
#line 115 "zparser.yy"
                          { driver.set_attrlist((yystack_[0].value.oabeAttrList)); }
#line 710 "zparser.tab.cc"
    break;

  case 4:
#line 117 "zparser.yy"
                                {
                                   if (!checkValidBit((yystack_[2].value.uintVal), (yystack_[0].value.uintVal))) {
                                      YYERROR;
                                   } else {
                                      (yylhs.value.uInteger) = create_expint((yystack_[2].value.uintVal), (yystack_[0].value.uintVal));
                                   }
                                }
#line 722 "zparser.tab.cc"
    break;

  case 5:
#line 124 "zparser.yy"
                                { (yylhs.value.uInteger) = create_flexint((yystack_[0].value.uintVal)); }
#line 728 "zparser.tab.cc"
    break;

  case 6:
#line 126 "zparser.yy"
                                { (yylhs.value.treeNode) = driver.leaf_node(*(yystack_[0].value.stringVal)); delete (yystack_[0].value.stringVal); }
#line 734 "zparser.tab.cc"
    break;

  case 7:
#line 127 "zparser.yy"
                                { (yylhs.value.treeNode) = driver.kof2_tree(1, (yystack_[2].value.treeNode), (yystack_[0].value.treeNode)); }
#line 740 "zparser.tab.cc"
    break;

  case 8:
#line 128 "zparser.yy"
                                { (yylhs.value.treeNode) = driver.kof2_tree(2, (yystack_[2].value.treeNode), (yystack_[0].value.treeNode)); }
#line 746 "zparser.tab.cc"
    break;

  case 9:
#line 129 "zparser.yy"
                                { (yylhs.value.treeNode) = driver.lt_policy(*(yystack_[2].value.stringVal), (yystack_[0].value.uInteger)); delete (yystack_[2].value.stringVal); delete (yystack_[0].value.uInteger); }
#line 752 "zparser.tab.cc"
    break;

  case 10:
#line 130 "zparser.yy"
                                { (yylhs.value.treeNode) = driver.gt_policy(*(yystack_[2].value.stringVal), (yystack_[0].value.uInteger)); delete (yystack_[2].value.stringVal); delete (yystack_[0].value.uInteger); }
#line 758 "zparser.tab.cc"
    break;

  case 11:
#line 131 "zparser.yy"
                                { (yylhs.value.treeNode) = driver.le_policy(*(yystack_[2].value.stringVal), (yystack_[0].value.uInteger)); delete (yystack_[2].value.stringVal); delete (yystack_[0].value.uInteger); }
#line 764 "zparser.tab.cc"
    break;

  case 12:
#line 132 "zparser.yy"
                                { (yylhs.value.treeNode) = driver.ge_policy(*(yystack_[2].value.stringVal), (yystack_[0].value.uInteger)); delete (yystack_[2].value.stringVal); delete (yystack_[0].value.uInteger); }
#line 770 "zparser.tab.cc"
    break;

  case 13:
#line 133 "zparser.yy"
                                { (yylhs.value.treeNode) = driver.eq_policy(*(yystack_[2].value.stringVal), (yystack_[0].value.uInteger)); delete (yystack_[2].value.stringVal); delete (yystack_[0].value.uInteger); }
#line 776 "zparser.tab.cc"
    break;

  case 14:
#line 134 "zparser.yy"
                                { (yylhs.value.treeNode) = (yystack_[1].value.treeNode); }
#line 782 "zparser.tab.cc"
    break;

  case 15:
#line 137 "zparser.yy"
                { (yylhs.value.treeNode) = driver.range_policy(*(yystack_[6].value.stringVal), (yystack_[3].value.uInteger), (yystack_[1].value.uInteger)); 
                  delete (yystack_[6].value.stringVal); delete (yystack_[3].value.uInteger); delete (yystack_[1].value.uInteger); 
                }
#line 790 "zparser.tab.cc"
    break;

  case 16:
#line 141 "zparser.yy"
                { (yylhs.value.treeNode) = driver.range_incl_policy(*(yystack_[6].value.stringVal), (yystack_[3].value.uInteger), (yystack_[1].value.uInteger)); 
                  delete (yystack_[6].value.stringVal); delete (yystack_[3].value.uInteger); delete (yystack_[1].value.uInteger); 
                }
#line 798 "zparser.tab.cc"
    break;

  case 17:
#line 146 "zparser.yy"
                { std::unique_ptr<L_OpenABEUInteger> month(get_month(*(yystack_[3].value.stringVal))); 
                  (yylhs.value.treeNode) = driver.set_date_in_policy(*(yystack_[5].value.stringVal), month.get(), (yystack_[2].value.uInteger), (yystack_[0].value.uInteger)); 
                  delete (yystack_[5].value.stringVal); delete (yystack_[3].value.stringVal); delete (yystack_[2].value.uInteger); delete (yystack_[0].value.uInteger);
                }
#line 807 "zparser.tab.cc"
    break;

  case 18:
#line 151 "zparser.yy"
                { std::unique_ptr<L_OpenABEUInteger> month(get_month(*(yystack_[5].value.stringVal))); 
                  (yylhs.value.treeNode) = driver.range_date_in_policy(*(yystack_[7].value.stringVal), month.get(), (yystack_[4].value.uInteger), (yystack_[2].value.uInteger), (yystack_[0].value.uInteger)); 
                  delete (yystack_[7].value.stringVal); delete (yystack_[5].value.stringVal); delete (yystack_[4].value.uInteger); delete (yystack_[2].value.uInteger); delete (yystack_[0].value.uInteger);
                }
#line 816 "zparser.tab.cc"
    break;

  case 19:
#line 156 "zparser.yy"
                { std::unique_ptr<L_OpenABEUInteger> month(get_month(*(yystack_[3].value.stringVal))); 
                  (yylhs.value.treeNode) = driver.gt_date_in_policy(*(yystack_[5].value.stringVal), month.get(), (yystack_[2].value.uInteger), (yystack_[0].value.uInteger)); 
                  delete (yystack_[5].value.stringVal); delete (yystack_[3].value.stringVal); delete (yystack_[2].value.uInteger); delete (yystack_[0].value.uInteger);
                }
#line 825 "zparser.tab.cc"
    break;

  case 20:
#line 161 "zparser.yy"
                { std::unique_ptr<L_OpenABEUInteger> month(get_month(*(yystack_[3].value.stringVal))); 
                  (yylhs.value.treeNode) = driver.lt_date_in_policy(*(yystack_[5].value.stringVal), month.get(), (yystack_[2].value.uInteger), (yystack_[0].value.uInteger)); 
                  delete (yystack_[5].value.stringVal); delete (yystack_[3].value.stringVal); delete (yystack_[2].value.uInteger); delete (yystack_[0].value.uInteger);
                }
#line 834 "zparser.tab.cc"
    break;

  case 21:
#line 166 "zparser.yy"
                { std::unique_ptr<L_OpenABEUInteger> month(get_month(*(yystack_[3].value.stringVal))); 
                  (yylhs.value.treeNode) = driver.ge_date_in_policy(*(yystack_[5].value.stringVal), month.get(), (yystack_[2].value.uInteger), (yystack_[0].value.uInteger)); 
                  delete (yystack_[5].value.stringVal); delete (yystack_[3].value.stringVal); delete (yystack_[2].value.uInteger); delete (yystack_[0].value.uInteger);
                }
#line 843 "zparser.tab.cc"
    break;

  case 22:
#line 171 "zparser.yy"
                { std::unique_ptr<L_OpenABEUInteger> month(get_month(*(yystack_[3].value.stringVal))); 
                  (yylhs.value.treeNode) = driver.le_date_in_policy(*(yystack_[5].value.stringVal), month.get(), (yystack_[2].value.uInteger), (yystack_[0].value.uInteger)); 
                  delete (yystack_[5].value.stringVal); delete (yystack_[3].value.stringVal); delete (yystack_[2].value.uInteger); delete (yystack_[0].value.uInteger);
                }
#line 852 "zparser.tab.cc"
    break;

  case 23:
#line 176 "zparser.yy"
                                { (yylhs.value.oabeAttrList) = driver.leaf_attr(*(yystack_[0].value.stringVal)); delete (yystack_[0].value.stringVal); }
#line 858 "zparser.tab.cc"
    break;

  case 24:
#line 177 "zparser.yy"
                                { (yylhs.value.oabeAttrList) = driver.concat_attr((yystack_[0].value.oabeAttrList), nullptr); }
#line 864 "zparser.tab.cc"
    break;

  case 25:
#line 178 "zparser.yy"
                                { (yylhs.value.oabeAttrList) = driver.concat_attr((yystack_[1].value.oabeAttrList), nullptr); }
#line 870 "zparser.tab.cc"
    break;

  case 26:
#line 179 "zparser.yy"
                                { (yylhs.value.oabeAttrList) = driver.concat_attr((yystack_[2].value.oabeAttrList), (yystack_[0].value.oabeAttrList)); delete (yystack_[0].value.oabeAttrList); }
#line 876 "zparser.tab.cc"
    break;

  case 27:
#line 180 "zparser.yy"
                                { (yylhs.value.oabeAttrList) = driver.attr_num(*(yystack_[2].value.stringVal), (yystack_[0].value.uInteger)); delete (yystack_[2].value.stringVal); delete (yystack_[0].value.uInteger); }
#line 882 "zparser.tab.cc"
    break;

  case 28:
#line 182 "zparser.yy"
                { std::unique_ptr<L_OpenABEUInteger> month(get_month(*(yystack_[3].value.stringVal))); 
                  (yylhs.value.oabeAttrList) = driver.set_date_in_attrlist(*(yystack_[5].value.stringVal), *(yystack_[3].value.stringVal), month.get(), (yystack_[2].value.uInteger), (yystack_[0].value.uInteger)); 
                  delete (yystack_[5].value.stringVal); delete (yystack_[3].value.stringVal); delete (yystack_[2].value.uInteger); delete (yystack_[0].value.uInteger);
                }
#line 891 "zparser.tab.cc"
    break;


#line 895 "zparser.tab.cc"

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
      YY_STACK_PRINT ();

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
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
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
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[+yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yy_error_token_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yy_error_token_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

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
  Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  // Generate an error message.
  std::string
  Parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    std::ptrdiff_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */
    if (!yyla.empty ())
      {
        symbol_number_type yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];

        int yyn = yypact_[+yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yy_error_token_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char Parser::yypact_ninf_ = -20;

  const signed char Parser::yytable_ninf_ = -1;

  const signed char
  Parser::yypact_[] =
  {
      17,    -2,     1,     7,    11,    -2,    44,   -13,     1,    -1,
     -20,    12,    51,    53,   -15,    55,    58,    34,     3,    -2,
      -2,    60,    -1,     1,    20,   -20,    12,   -20,    12,   -20,
      12,    12,    12,   -20,    12,   -20,    12,   -20,    56,   -20,
      12,   -20,    -1,    62,    39,    40,    45,    46,    43,    47,
     -19,    48,   -20,    12,    12,    12,    12,    12,    12,    12,
      12,    12,   -20,   -20,    49,    52,   -20,   -20,    54,   -20,
     -20,   -20,   -20,    12,   -20
  };

  const signed char
  Parser::yydefact_[] =
  {
       0,     0,     0,     0,     6,     0,     2,    23,     0,     3,
       1,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    24,    25,     5,    13,     0,    11,     0,    12,
       0,     0,     0,     9,     0,    10,     0,    14,     7,     8,
       0,    27,    26,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     4,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    22,    21,     0,     0,    20,    19,     0,    17,
      28,    15,    16,     0,    18
  };

  const signed char
  Parser::yypgoto_[] =
  {
     -20,   -20,   -12,    31,    29
  };

  const signed char
  Parser::yydefgoto_[] =
  {
      -1,     3,    25,     6,     9
  };

  const signed char
  Parser::yytable_[] =
  {
      27,    29,     4,    33,    35,     7,    59,    10,    30,    41,
      60,    31,    19,    20,    44,    21,    45,    24,    46,    47,
      48,     5,    49,    11,    50,    12,    13,    37,    51,    23,
      14,     8,    15,    16,     1,     2,    18,    22,    36,    17,
      43,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      38,    39,    42,    19,    20,    26,    24,    28,    24,    32,
      24,    74,    34,    24,    40,    24,    20,    52,    53,    54,
      55,    56,    57,    71,     0,     0,    58,    61,     0,    72,
       0,     0,     0,    73
  };

  const signed char
  Parser::yycheck_[] =
  {
      12,    13,     4,    15,    16,     4,    25,     0,    23,    21,
      29,    26,     9,    10,    26,    28,    28,     5,    30,    31,
      32,    23,    34,    12,    36,    14,    15,    24,    40,    30,
      19,    30,    21,    22,    17,    18,     5,     8,     4,    28,
      20,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      19,    20,    23,     9,    10,     4,     5,     4,     5,     4,
       5,    73,     4,     5,     4,     5,    10,     5,    29,    29,
      25,    25,    29,    24,    -1,    -1,    29,    29,    -1,    27,
      -1,    -1,    -1,    29
  };

  const signed char
  Parser::yystos_[] =
  {
       0,    17,    18,    32,     4,    23,    34,     4,    30,    35,
       0,    12,    14,    15,    19,    21,    22,    28,    34,     9,
      10,    28,    35,    30,     5,    33,     4,    33,     4,    33,
      23,    26,     4,    33,     4,    33,     4,    24,    34,    34,
       4,    33,    35,    20,    33,    33,    33,    33,    33,    33,
      33,    33,     5,    29,    29,    25,    25,    29,    29,    25,
      29,    29,    33,    33,    33,    33,    33,    33,    33,    33,
      33,    24,    27,    29,    33
  };

  const signed char
  Parser::yyr1_[] =
  {
       0,    31,    32,    32,    33,    33,    34,    34,    34,    34,
      34,    34,    34,    34,    34,    34,    34,    34,    34,    34,
      34,    34,    34,    35,    35,    35,    35,    35,    35
  };

  const signed char
  Parser::yyr2_[] =
  {
       0,     2,     2,     2,     3,     1,     1,     3,     3,     3,
       3,     3,     3,     3,     3,     7,     7,     6,     8,     6,
       6,     6,     6,     1,     2,     2,     3,     3,     6
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\"end of line\"",
  "\"string\"", "\"an integer\"", "\"OpenABEUInteger\"",
  "\"OpenABE tree node\"", "\"OpenABE attribute list\"", "OR", "AND",
  "\"of\"", "\"==\"", "\"=\"", "\"<=\"", "\">=\"", "\"error\"", "\"[0]:\"",
  "\"[1]:\"", "\"in\"", "'#'", "'<'", "'>'", "'('", "')'", "'-'", "'{'",
  "'}'", "'='", "','", "'|'", "$accept", "start", "number", "policy",
  "attrlist", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned char
  Parser::yyrline_[] =
  {
       0,   114,   114,   115,   117,   124,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   136,   140,   145,   150,   155,
     160,   165,   170,   176,   177,   178,   179,   180,   181
  };

  // Print the state stack on the debug stream.
  void
  Parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  Parser::yy_reduce_print_ (int yyrule)
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

  Parser::token_number_type
  Parser::yytranslate_ (int t)
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const token_number_type
    translate_table[] =
    {
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,    20,     2,     2,     2,     2,
      23,    24,     2,     2,    29,    25,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      21,    28,    22,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    26,    30,    27,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19
    };
    const int user_token_number_max_ = 274;

    if (t <= 0)
      return yyeof_;
    else if (t <= user_token_number_max_)
      return translate_table[t];
    else
      return yy_undef_token_;
  }

//} // test
#line 1368 "zparser.tab.cc"

#line 192 "zparser.yy"
 /*** Additional Code ***/

void Parser::error(const Parser::location_type& l,
			    const std::string& m)
{
    driver.error(l, m);
}
