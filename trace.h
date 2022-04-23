#ifdef TRACE_STATE
#define STATE(S) node_t* S (istream& in, Token& tk) { \
    enterState(#S);
#else
#define STATE(S) node_t* S (istream& in, Token& tk) {
#endif
#define END(S, P) return exitState(#S, P);  }
​
#ifdef TRACE_STATE
#define ENTER_STATE
#define EXIT_STATE
#endif
​
#ifdef ENTER_STATE
void enterState(string node) {
#ifdef TRACE_TOKENS
    cout << endl;
#endif
  switch(toupper(node.at(0))) {
    case 'S':
        cout << "<S> -> Name Identifier Spot Identifier <R> <E>" << endl;
        break;
    case 'R':
        cout << "<R> -> Place <A> <B> Home" << endl;
        break;
    case 'E':
        cout << "<E> -> Show Identifier" << endl;
        break;
    case 'A':
        cout << "<A> -> Name Identifier" << endl;
        break;
    case 'B':
        cout << "<B> -> empty | . <C> . <B> | <D> <B>" << endl;
        break;
    case 'C':
        cout << "<C> -> <F> | <G>" << endl;
        break;
    case 'D':
        cout << "<D> -> <H>|<J>|<K>|<L> |<E>|<F>" << endl;
        break;
    case 'F':
        cout << "<F> -> { If Identifier <T> <W> <D> } | { Do Again <D> <T> <W> }" << endl;
        break;
    case 'G':
        cout << "<G> -> Here Number There" << endl;
        break;
    case 'T':
        cout << "<T> -> << | <- " << endl;
        break;
    case 'V':
        cout << "<V> -> + | % | & " << endl;
        break;
    case 'H':
        cout << "<H> -> / <Z>" << endl;
        break;
    case 'K':
        cout << "<K> -> Spot Number Show Number | Move Identifer Show Identifier" << endl;
        break;
    case 'L':
        cout << "<L> -> Flip Identifier" << endl;
        break;
    case 'W':
        cout << "<W> -> Number <V> Number | Number ." << endl;
        break;
    case 'J':
        cout << "<J> -> Assign Identifier <D>" << endl;
        break;
    case 'Z':
        cout << "<Z> -> Identifier | Number" << endl;
        break;
    default:
        cout << "missing case <" << node << ">" << endl;
        exit(-1);
        break;
    }
    cout << "   ";
}
#else
void inform(char node) {
    cout << endl;
}
#endif
​
#ifdef EXIT_STATE
node_t* exitState(string node, node_t *p) {
#ifdef TRACE_TOKENS
    cout << endl;
#endif
    cout << "    <" << node << "> returns";
#ifndef TRACE_TOKENS
    cout << endl;
#endif
    return p;
}
#else
node_t* exitState(string node, node_t *p) {
    return p;
}
#endif
