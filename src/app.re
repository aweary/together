external innerWidth : int = "window.innerWidth" [@@bs.val];

external innerHeight : int = "window.innerHeight" [@@bs.val];

module App = {
  include ReactRe.Component;
  type props = {title: string};
  let name = "App";
  let emojis =
    Js.Array.map
      (fun emoji => <ProgressiveEmoji emoji />)
      (Emoji.getPeople ());
  let render _ =>
    <div className="app">
      <h1 className="header"> (ReactRe.stringToElement "Together") </h1>
      (ReactRe.arrayToElement emojis)
    </div>;
};

include ReactRe.CreateComponent App;

let createElement ::title => wrapProps {title: title};