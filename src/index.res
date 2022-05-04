let {render, querySelector} = module(ReactDOM)

switch querySelector("#root") {
| None => ()
| Some(e) => render(<App />, e)
}
