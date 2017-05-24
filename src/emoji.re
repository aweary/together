/* Defer to lodash.flatten for array flattening */

external flatten : Js.Array.t (Js.Array.t 'a) => Js.Array.t 'a = "lodash.flatten" [@@bs.module];

external shuffle : Js.Array.t 'a => Js.Array.t 'a = "lodash.shuffle" [@@bs.module];

external getCodePoint : string => string = "toCodePoint" [@@bs.module "twemoji"] [@@bs.scope "convert"];

let joiner = Js.String.fromCodePoint 8205;

let woman = {js|👩|js};

let man = {js|👨|js};

let genders = [| {js|♂️|js}, {js|♀️|js} |];
let skinTones = [|{js|🏻|js}, {js|🏼|js}, {js|🏽|js}, {js|🏾|js}, {js|🏿|js}|];


/* Each emoji or modifier is represented by a code point. We could
   just store the character instead since BuckleScript supports Unicode,
   but for now this is fine */
let mapToProfessions professions people =>
  professions
  |> Js.Array.map
    (fun profession => Js.Array.map (fun person => person ^ joiner ^ profession) people)
  |> flatten;

let mapToSkinTones people =>
people
|> Js.Array.map (fun profession => {
  Js.Array.map (fun tone => profession ^ tone) skinTones;
})
|> flatten;

let mapToGenders people =>
  people
  |> Js.Array.map (fun person => {
    Js.Array.map (fun gender => person ^ joiner ^ gender) genders
  })
  |> flatten;
let professions = [|
  {js|⚕️|js},
  {js|🎓|js},
  {js|🏫|js},
  {js|🌾|js},
  {js|🍳|js},
  {js|🔧|js},
  {js|🏭|js},
  {js|💼|js},
  {js|🔬|js},
  {js|💻|js},
  {js|🎤|js},
  {js|🎨|js},
  {js|✈️|js},
  {js|🚀|js},
  {js|🚒|js}
|];

let nonSequencedProfessions = [|
  {js|👮|js},
  {js|🕵️|js},
  {js|👷|js},
  {js|👳|js},
  {js|👱|js}
|]
|> mapToSkinTones
|> mapToGenders;

let people =
  Js.Array.concat
    (Js.Array.map (fun tone => woman ^ tone) skinTones)
    (Js.Array.map (fun tone => man ^ tone) skinTones);

let sequencedProfessions = people |> mapToProfessions professions |> shuffle;

let getPeople () => nonSequencedProfessions
  |> Js.Array.concat sequencedProfessions
  |> shuffle;