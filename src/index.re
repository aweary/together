// let {render, querySelector} = module(ReactDOM)

switch (ReactDOM.querySelector("#root")) {
| None => ()
| Some(e) => ReactDOM.render(<App />, e)
}