[@new] external createImage: unit => Dom.element = "Image";
[@set] external setImageSrc: (Dom.element, string) => unit = "src";
[@set] external onImageLoad: (Dom.element, 'a => unit) => unit = "onload";

type state = {
  loaded: bool,
  src: string,
};

let getTwemojiSource = emoji => {
  let codePoint = Emoji.getCodePoint(emoji);
  "https://twemoji.maxcdn.com/2/svg/" ++ codePoint ++ ".svg";
};
[@react.component]
let make = (~emoji: string) => {
  let initialState = {loaded: false, src: getTwemojiSource(emoji)};
  let (state, setState) = React.useState(_ => initialState);
  //   let emojis =
  //     Js.Array.map(emoji => <ProgressiveEmoji emoji />, Emoji.getPeople());\

  let people = Emoji.getPeople();
  let emojis =
    Js.Array.map(emoji => <img className="emoji" src=emoji />, people);

  React.useEffect2(
    () => {
      let image = createImage();

      onImageLoad(image, _ => {setState(state => {...state, loaded: true})});
      setImageSrc(image, state.src);
      None;
    },
    (state, setState),
  );

  <div className="app">
    <h1 className="header"> {React.string("Together")} </h1>
    {React.array(emojis)}
  </div>;
};
