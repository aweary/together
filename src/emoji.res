/* Defer to lodash.flatten for array flattening */

@module
external flatten: array<array<'a>> => array<'a> = "lodash.flatten"

@module external shuffle: array<'a> => array<'a> = "lodash.shuffle"

@module("twemoji") @scope("convert")
external getCodePoint: string => string = "toCodePoint"

let joiner = Js.String.fromCodePoint(8205)

let woman = `👩`

let man = `👨`

let genders = [`♂️`, `♀️`]
let skinTones = [`🏻`, `🏼`, `🏽`, `🏾`, `🏿`]

/* Each emoji or modifier is represented by a code point. We could
   just store the character instead since BuckleScript supports Unicode,
   but for now this is fine */
let mapToProfessions = (professions, people) =>
  professions
  |> Js.Array.map(profession => Js.Array.map(person => person ++ (joiner ++ profession), people))
  |> flatten

let mapToSkinTones = people =>
  people
  |> Js.Array.map(profession => Js.Array.map(tone => profession ++ tone, skinTones))
  |> flatten

let mapToGenders = people =>
  people
  |> Js.Array.map(person => Js.Array.map(gender => person ++ (joiner ++ gender), genders))
  |> flatten
let professions = [
  `⚕️`,
  `🎓`,
  `🏫`,
  `🌾`,
  `🍳`,
  `🔧`,
  `🏭`,
  `💼`,
  `🔬`,
  `💻`,
  `🎤`,
  `🎨`,
  `✈️`,
  `🚀`,
  `🚒`,
]

let nonSequencedProfessions =
  [`👮`, `🕵️`, `👷`, `👳`, `👱`] |> mapToSkinTones |> mapToGenders

let people = Js.Array.concat(
  Js.Array.map(tone => woman ++ tone, skinTones),
  Js.Array.map(tone => man ++ tone, skinTones),
)

let sequencedProfessions = people |> mapToProfessions(professions) |> shuffle

let getPeople = () => nonSequencedProfessions |> Js.Array.concat(sequencedProfessions) |> shuffle
