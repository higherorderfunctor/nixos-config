/* eslint-disable max-classes-per-file */
import { FileSystem } from '@effect/platform/FileSystem';
import { ParseResult } from '@effect/schema';
import * as S from '@effect/schema/Schema';
import { Gio } from '@girs/gio-2.0';
import { GObject } from '@girs/gobject-2.0';
import { Gtk } from '@girs/gtk-4.0';
import type { Types } from 'effect';
import { Cause, Console, Context, Effect, Exit, Layer, Option, pipe, ReadonlyArray, Struct } from 'effect';
import type { NonEmptyReadonlyArray } from 'effect/ReadonlyArray';

import { GjsFileSystem } from './platform-gjs/index.js';

const User = S.struct({
  username: S.string.pipe(S.nonEmpty()),
  uid: S.number,
  gid: S.number,
  name: S.transform(
    S.string,
    S.optionFromSelf(S.string.pipe(S.nonEmpty())),
    (s) => (s ? Option.some(s) : Option.none()),
    (n) => Option.getOrElse(n, () => ''),
  ),
  homedir: S.string.pipe(S.nonEmpty()),
  shell: S.string.pipe(S.nonEmpty()),
});

interface User extends S.Schema.Type<typeof User> {}

export const PasswdToUser = S.transformOrFail(
  S.Trim.pipe(S.compose(S.split(':'))),
  User,
  (passwd) =>
    pipe(
      S.decodeUnknown(
        S.tuple(S.string, S.string, S.NumberFromString, S.NumberFromString, S.string, S.string, S.string),
      )(passwd),
      Effect.mapBoth({
        onFailure: (e) => new ParseResult.Type(S.string.ast, passwd, e.message),
        onSuccess: ([username, , uid, gid, gecos, homedir, shell]) => {
          const [name] = gecos.split(',');
          return {
            username,
            uid,
            gid,
            name,
            homedir,
            shell,
          };
        },
      }),
    ),
  (user) =>
    ParseResult.succeed([
      user.username,
      'x',
      user.uid.toString(),
      user.gid.toString(),
      user.name,
      user.homedir,
      user.shell,
    ]),
);

const getUsers = Effect.gen(function* (_) {
  const fs = yield* _(FileSystem);
  const passwd = yield* _(fs.readFileString('/etc/passwd', 'utf-8'));
  return yield* _(
    pipe(
      passwd.split('\n'),
      ReadonlyArray.map((passwd) => S.decode(PasswdToUser)(passwd)),
      Effect.allSuccesses,
      Effect.map(
        ReadonlyArray.filter(
          (user) => !(!!user.shell.includes('nologin') || user.shell === '/var/empty' || user.username === 'root'),
        ),
      ),
    ),
  );
});

const LoginBox = (usernameField: Gtk.Widget, passwordField: Gtk.Widget) =>
  Widget.Box({
    // setup: (self) => {
    //   console.log('here');
    // },
    // on_focus_enter: () => {
    //   console.log('hi');
    // },
    children: [
      Widget.Overlay({
        hexpand: true,
        vexpand: true,
        child: Widget.Box({
          vertical: true,
          vpack: 'center',
          hpack: 'center',
          spacing: 16,
          children: [
            //   Widget.Box({
            //     hpack: 'center',
            //     class_name: 'avatar',
            //   }),
            Widget.Box({
              cssClasses: ['entry-box'],
              vertical: true,
              children: [usernameField, Widget.Separator(), passwordField],
            }),
          ],
        }),
        // overlays: [
        //   RoundedCorner('topleft', { class_name: 'corner' }),
        //   RoundedCorner('topright', { class_name: 'corner' }),
        // ],
      }),
    ],
  });

const GreeterWindow = <Child extends Gtk.Widget = Gtk.Widget>(child: Child) =>
  Widget.Window({
    name: 'greeter',
    keymode: 'on-demand', // TODO: exclusive
    cssClasses: ['base'],
    child: Widget.Box({
      vertical: true,
      children: [child],
    }),
  });

class Greeter extends Context.Tag('Greeter')<Greeter, { window: Gtk.Window }>() {}
// const password = Entry({
//     placeholderText: 'Password',
//     visibility: false,
//
//     setup: (self) => idle(() => {
//         self.grab_focus();
//     }),
//
//     on_accept: () => {
//         greetd.login(
//             (dropdown.selectedItem as StringObject)['string'] || '',
//             password.text || '',
//             'Hyprland',
//
//         ).catch((error) => {
//             response.label = JSON.stringify(error);
//         });
//     },
//
// });

//  enableSearch?: boolean | null
//  /**
//   * An expression to evaluate to obtain strings to match against the search
//   * term.
//   *
//   * See [property`Gtk`.DropDown:enable-search] for how to enable search.
//   * If [property`Gtk`.DropDown:factory] is not set, the expression is also
//   * used to bind strings to labels produced by a default factory.
//   */
//  expression?: Expression | null
//  factory?: ListItemFactory | null
//  headerFactory?: ListItemFactory | null
//  listFactory?: ListItemFactory | null
//  model?: Gio.ListModel | null
//  searchMatchMode?: StringFilterMatchMode | null
//  selected?: number | null
//  showArrow?: boolean | null

type DropDownProps = Types.Simplify<
  Omit<Gtk.DropDown.ConstructorProperties, 'model'> & {
    model?: Gio.ListModel | NonEmptyReadonlyArray<string> | null;
  }
>;

const defaultDropDownProperties = {
  enableSearch: true,
  // expression: new Gtk.PropertyExpression(Gtk.StringObject.$gtype, null, 'string'),
  // factory?: ListItemFactory | null,
  // headerFactory?: ListItemFactory | null,
  // listFactory?: ListItemFactory | null,
  // model?: Gio.ListModel | null,
  searchMatchMode: Gtk.StringFilterMatchMode.SUBSTRING,
  selected: 0,
  showArrow: true,
};

const DropDownItem = GObject.registerClass(
  {
    // Registered name should be unique
    GTypeName: `DropDownItem${Math.floor(Math.random() * 1000)}`,
    Properties: {
      text: GObject.ParamSpec.string('text', 'Text', 'DropDown item text', GObject.ParamFlags.READWRITE, ''),
      id: GObject.ParamSpec.int(
        'id',
        'Id',
        'Item id stored in settings',
        GObject.ParamFlags.READWRITE,
        // min, max, default
        -65535,
        65535,
        0,
      ),
    },
  },
  class DropDownItem extends GObject.Object {
    _id: string;

    _text: string;

    constructor({ id, text }: { id: string; text: string }) {
      super();
      this._id = id;
      this._text = text;
    }

    get text() {
      return this._text;
    }

    set text(text) {
      this._text = text;
    }

    get id() {
      return this._id;
    }

    set id(id) {
      this._id = id;
    }
  },
);

type DropDownItem = InstanceType<typeof DropDownItem>;

class DropDown extends Gtk.DropDown {
  static {
    GObject.registerClass({ GTypeName: 'EffectDropDown' }, this);
  }

  // https://github.com/tuberry/user-theme-x/blob/6e85852606e380d0e1d3a65ecf2f08985a5a280f/src/prefs.js#L22
  constructor(config: DropDownProps) {
    const configWithDefaults = { ...config, ...defaultDropDownProperties };
    // const model = Gtk.StringList.new(['asdf', 'asdfdadsf', 'gjdjs']);

    // const model = Gio.ListModel;

    const model = new Gio.ListStore<DropDownItem>(DropDownItem.$gtype);
    model.append(new DropDownItem({ id: 'apple', text: 'APPLE' }));
    model.append(new DropDownItem({ id: 'banana', text: 'BANANA' }));
    model.append(new DropDownItem({ id: 'cherry', text: 'CHERRY' }));

    const filter = new Gtk.StringFilter({
      expression: new Gtk.PropertyExpression(DropDownItem.$gtype, null, 'text'),
      matchMode: configWithDefaults.searchMatchMode,
    });
    const searchableModel = new Gtk.FilterListModel({ model, filter });

    const factory = new Gtk.SignalListItemFactory();
    factory.connect('setup', (_, listItem: Gtk.ListItem) => {
      console.log('setup');
      const label = new Gtk.Label({ xalign: 0 });
      listItem.set_child(label);
    });
    factory.connect('bind', (_, listItem: Gtk.ListItem) => {
      console.log('bind');
      const label = listItem.get_child() as unknown as Gtk.Label;
      const item = listItem.get_item() as unknown as DropDownItem;
      label.set_text(item.text);
    });

    super({
      ...configWithDefaults,
      model: searchableModel /* , valign: Gtk.Align.CENTER, tooltipText */,
      factory,
    });

    filter.set_search('A');
    const popover = Option.fromNullable(this.get_last_child()).pipe(
      Option.flatMap((self) => Option.fromNullable(self.get_first_child())),
      Option.flatMap((self) => Option.fromNullable(self.get_first_child())),
      Option.flatMap((self) => Option.fromNullable(self.get_first_child())),
      Option.flatMap((self) => Option.fromNullable(self.get_first_child())),
      Option.tap((searchEntry) => {
        searchEntry.connect('search-changed', (search: Gtk.SearchEntry) => {
          console.log(search.text);
          filter.set_search(search.text);
        });
        return Option.some(searchEntry);
      }),
    );
    // const content = this.get_last_child();
    // const box = content.get_first_child();
    // const box2 = box.get_first_child();
    // const search_entry = box2.get_first_child();

    // console.log(model);
    // this.set_list_factory(this.factory);

    // Apply the factory to the DropDown
    // if (strv.length > 7) {
    //   this.set_enable_search(true);
    //   this.set_search_match_mode(Gtk.StringFilterMatchMode.SUBSTRING);
    //   this.set_expression(new Gtk.PropertyExpression(Gtk.StringObject.$gtype, null, 'string'));
    // }
    // this.set_list_factory(this.factory);
    // const listItemFactory: Gtk.ListItemFactory = hook(
    //   {
    //     setup: (_f, x) => x.set_child(new UI.IconLabel(icon_name)),
    //     bind: (_f, x) => x.get_child().setContent(null, x.item.string),
    //   },
    //   new Gtk.SignalListItemFactory(),
    // );
    // this.set_factory(
    //   hook(
    //     {
    //       setup: (_f, x) => x.set_child(new UI.IconLabel(icon_name)),
    //       bind: (_f, x) => x.get_child().setContent(null, x.item.string),
    //     },
    //     new Gtk.SignalListItemFactory(),
    //   ),
    // );
    // this.bind_property_full(
    //   'value',
    //   this,
    //   'selected',
    //   GObject.BindingFlags.BIDIRECTIONAL | GObject.BindingFlags.SYNC_CREATE,
    //   (_b, data) => {
    //     let ret = this.model.get_n_items();
    //     do ret--;
    //     while (ret > -1 && data !== this.model.get_item(ret).string);
    //     return [ret !== -1, ret];
    //   },
    //   (_b, data) => [data !== Gtk.INVALID_LIST_POSITION, this.model.get_item(data)?.string ?? ''],
    // );
  }
}
const GreeterLive = Layer.effect(
  Greeter,
  Effect.gen(function* (_) {
    const users = yield* _(getUsers);

    // const usernameDropdown = Gtk.DropDown.new_from_strings([
    //   // FIXME: 'asdf',
    //   'asdf',
    //   'select',
    //   ...users.map((u) => Option.getOrElse(u.name, () => u.username)),
    // ]);

    // usernameDropdown.enableSearch = true;

    const usernameDropdown = new DropDown({
      model: [
        // FIXME: 'asdf',
        'asdf',
        'select',
        ...users.map((u) => Option.getOrElse(u.name, () => u.username)),
      ],
    });

    // const stringList = new Gtk.StringList();

    // Add items to the string list
    // [
    //   // FIXME: 'asdf',
    //   'asdf',
    //   'select',
    //   ...users.map((u) => Option.getOrElse(u.name, () => u.username)),
    // ].forEach((item) => {
    //   stringList.append(item);
    // });

    // // Create a DropDown widget
    // const usernameDropdown = new Gtk.DropDown({
    //   model: stringList, // Set the model for the DropDown
    //   enableSearch: true, // Enable search functionality
    // });

    // Use set_expression to define how to present the items from the model in the DropDown
    // Since we're using a StringList, we directly bind the string items to be displayed.
    // usernameDropdown.expression = new Gtk.ClosureExpression(GObject.TYPE_STRING, (obj) => obj.string, null);
    // usernameDropdown.set_expression(new Gtk.PropertyExpression(Gtk.StringObject.$gtype, null, 'string'));
    // usernameDropdown.set_search_match_mode(Gtk.StringFilterMatchMode.SUBSTRING);
    // usernameDropdown.valu;

    // https://github.com/matt1432/nixos-configs/blob/2226b33bc866e17d8752396046367a49d235a8c7/modules/ags/astal/ts/greetd/main.ts#L6
    const passwordField = Widget.Entry({
      placeholderText: 'Password',
      visibility: false,
      setup: (self) =>
        Utils.idle(() => {
          self.grab_focus();
        }),
      // onAccept: () => handle_input().catch(logError),
    }); // .on('realize', (entry) => entry.grabFocus());

    const loginBox = LoginBox(usernameDropdown, passwordField);

    const greeterWindow = GreeterWindow(loginBox);

    return Greeter.of({
      window: greeterWindow,
    });
  }),
);

Effect.gen(function* (_) {
  const greeter = yield* _(Greeter);

  App.config({
    // icons: './assets',
    style: `${App.configDir}/assets/css/style.css`,
    windows: () => [greeter.window],
  });
})
  .pipe(
    Effect.tapError(Console.log),
    Effect.tapDefect(Console.log),
    Effect.forkDaemon,
    Effect.provide(GreeterLive.pipe(Layer.provide(GjsFileSystem.layer))),
    Effect.runPromiseExit,
  )
  .then((exit) => {
    if (Exit.isFailure(exit)) print(Cause.pretty(exit.cause));
    return exit;
  })
  .catch((error: unknown) => {
    print(error);
  });

// const handle_response = async (res) => {
//   if (!res) return;
//   let next_resp;
//   switch (res.type) {
//     case 'success':
//       if (state.value === 'starting') App.quit();
//       setState('starting');
//       next_resp = await Greetd.startSession([get_selected_DE()]);
//       break;
//     case 'error':
//       Greetd.cancelSession();
//       setState('username');
//       break;
//     case 'auth_message':
//       switch (res.auth_message_type) {
//         case 'secret':
//           setState('secret', `${res.auth_message}`);
//           break;
//         case 'visible':
//           setState('visible', `${res.auth_message}`);
//           break;
//         case 'info':
//           label.label = `${res.auth_message}`;
//           next_resp = await Greetd.postAuth();
//           break;
//         case 'error':
//           label.label = `${res.auth_message}`;
//           next_resp = await Greetd.postAuth();
//           break;
//       }
//       break;
//   }
//   return handle_response(next_resp);
// };
//
// const handle_input = async () => {
//   let res;
//   switch (state.value) {
//     case 'username':
//       res = await Greetd.createSession(entry.text);
//       entry.text = '';
//       break;
//     case 'auth':
//       res = await Greetd.postAuth(entry.text);
//       entry.text = '';
//       break;
//   }
//   return handle_response(res);
// };

// const password = Entry({
//     placeholderText: 'Password',
//     visibility: false,
//
//     setup: (self) => idle(() => {
//         self.grab_focus();
//     }),
//
//     on_accept: () => {
//         greetd.login(
//             (dropdown.selectedItem as StringObject)['string'] || '',
//             password.text || '',
//             'Hyprland',
//
//         ).catch((error) => {
//             response.label = JSON.stringify(error);
//         });
//     },
//
// });

// App.config({
//   style: `${App.configDir}/style.css`,
// });
// #!/usr/bin/ags -c
//
// import Greetd from "resource:///com/github/Aylur/ags/service/greetd.js";
// import Widget from "resource:///com/github/Aylur/ags/widget.js";
// import { RoundedAngleEnd, RoundedCorner } from "./modules/roundedCorner/index.js";
// import Clock from "./modules/clock/index.js";
// import SessionBox from "./modules/powermenu/index.js";
// import Gtk from "gi://Gtk?version=3.0";
// import { get_selected_DE } from "./modules/powermenu/index.js";
//
// const state = Variable("username");
//
// const label = Widget.Label("Enter username:");
// const entry = Widget.Entry({
//   hpack: "center",
//   xalign: 0.5,
//   placeholder_text: "password",
//   on_accept: () => handle_input().catch(logError)
// }).on("realize", (entry) => entry.grab_focus());
//
//
// function setState(stat, msg) {
//   switch(stat) {
//     case "username":
//       state.value =  "username";
//       entry.visibility = true;
//       label.label = "Enter username:";
//       break;
//     case "secret":
//       state.value =  "auth";
//       entry.visibility = false;
//       label.label = msg || "Enter password:";
//       break;
//     case "visible":
//       state.value =  "auth";
//       entry.visibility = true;
//       label.label = msg || "Enter password:";
//       break;
//     case "starting":
//       state.value =  "starting";
//       break;
//   }
// }
//
//
// const Right = () => Widget.Box({
//   hpack: "end",
//   children: [
//     RoundedAngleEnd("topleft", {class_name: "angle", hexpand: true}),
//     Clock(),
//   ]
// });
//
// const Left = () => Widget.Box({
//   children: [
//     SessionBox(),
//     RoundedAngleEnd("topright", {class_name: "angle"})
//   ]
// });
//
// const Bar = () => Widget.CenterBox({
//   start_widget: Left(),
//   end_widget: Right(),
// });
//
// const LoginBox = () => Widget.Box({
//   children: [
//     Widget.Overlay({
//       hexpand: true,
//       vexpand: true,
//       child: Widget.Box({
//         vertical: true,
//         vpack: "center",
//         hpack: "center",
//         spacing: 16,
//         children: [
//           Widget.Box({
//             hpack: "center",
//             class_name: "avatar",
//           }),
//           Widget.Box({
//             class_name: "entry-box",
//             vertical: true,
//             children: [
//               label,
//               Widget.Separator(),
//               entry,
//             ]
//           })
//         ]
//       }),
//       overlays: [
//         RoundedCorner("topleft", {class_name: "corner"}),
//         RoundedCorner("topright", {class_name: "corner"}),
//       ]
//     })
//   ]
// })
//
//
//
// async function handle_response(res) {
//   if(!res) return;
//   let next_resp;
//   switch(res.type) {
//     case "success":
//       if(state.value === "starting") App.quit();
//       setState("starting")
//       next_resp = await Greetd.startSession([get_selected_DE()]);
//       break;
//     case "error":
//       Greetd.cancelSession();
//       setState("username");
//       break;
//     case "auth_message":
//       switch(res.auth_message_type){
//         case "secret":
//           setState("secret", `${res.auth_message}`);
//           break;
//         case "visible":
//           setState("visible", `${res.auth_message}`);
//           break;
//         case "info":
//           label.label = `${res.auth_message}`
//           next_resp = await Greetd.postAuth();
//           break;
//         case "error":
//           label.label = `${res.auth_message}`
//           next_resp = await Greetd.postAuth();
//           break;
//       }
//       break;
//   }
//   return handle_response(next_resp);
// }
//
// async function handle_input() {
//   let res;
//   switch(state.value){
//     case "username":
//       res = await Greetd.createSession(entry.text);
//       entry.text = "";
//       break;
//     case "auth":
//       res = await Greetd.postAuth(entry.text);
//       entry.text = "";
//       break;
//   }
//   return handle_response(res);
// }
//
// App.config({
//   style: `${App.configDir}/style.css`,
// })
