external createImage : unit => Dom.element = "Image" [@@bs.new];
external setImageSrc : Dom.element => string => unit = "src" [@@bs.set];
external onImageLoad : Dom.element => ('a => unit) => unit = "onload" [@@bs.set];

module ProgressiveEmoji = {
  include ReactRe.Component.Stateful;
  type props = { emoji: string };
  type state = { loaded: bool, src: string };
  let name = "ProgressiveEmoji";

  let getTwemojiSource emoji => {
    let codePoint = Emoji.getCodePoint emoji;
    ("https://twemoji.maxcdn.com/2/svg/" ^ codePoint ^ ".svg");
  };
  let getInitialState props => {
    loaded: false,
    src: getTwemojiSource props.emoji
  };
  let componentDidMount { state, setState } => {
    let image = createImage ();
    onImageLoad image (fun _ => {
      setState (fun { state } => { ...state, loaded: true });
    });
    setImageSrc image state.src;
    None
  };
  let emojis =
    Js.Array.map
      (fun emoji => <img className="emoji" src=emoji />)
      (Emoji.getPeople ());
  let render { state, props } =>
    switch state.loaded {
    | false => <span className="emoji"> (ReactRe.stringToElement props.emoji) </span>
    | _ => <img className="emoji" src=state.src />
    }
};

include ReactRe.CreateComponent ProgressiveEmoji;

let createElement ::emoji => wrapProps {emoji: emoji};