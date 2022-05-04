[@bs.val] external innerWidth: int = "window.innerWidth";

[@bs.val] external innerHeight: int = "window.innerHeight";

[@react.component]
let make = () => {
  let emojis =
    Js.Array.map(emoji => <ProgressiveEmoji emoji />, Emoji.getPeople());
  <div className="app">
    <h1 className="header"> {React.string("Together")} </h1>
    {React.array(emojis)}
  </div>;
};
