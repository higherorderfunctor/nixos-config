import { FileSystem } from '@effect/platform/FileSystem';
import { ParseResult } from '@effect/schema';
import * as S from '@effect/schema/Schema';
import { Console, Effect, Option, pipe, ReadonlyArray } from 'effect';

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

// class User extends Data.TaggedClass('User')<{
//   username: string;
//   uid: number;
//   gid: number;
//   name: string;
//   homedir: string;
//   shell: string;
// }> {
//   static fromPasswd = (passwd: string) => {
//     const [username, , uid, gid, gecos, homedir, shell] = passwd.split(':');
//     const [name] = gecos.split(',');
//     return new User({
//       username,
//       uid: parseInt(uid),
//       gid: parseInt(gid),
//       name,
//       homedir,
//       shell,
//     });
//   };
// }
// - Username: jdoe
// - Password: An x, indicating the hashed password is stored in /etc/shadow
// - UID: 1001
// - GID: 1001
// - GECOS: John Doe,,, (additional user information, with some fields left blank)
// - Home Directory: /home/jdoe
// - Login Shell: /bin/bash

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

await Effect.runPromise(getUsers.pipe(Effect.tap(Console.log), Effect.provide(GjsFileSystem.layer)));

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

// const UsernameField = () =>
const UsernameField = Widget.Entry({
  placeholderText: 'Username',
  // on_accept: () => PasswordEntry.grab_focus(),
});
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

// const PasswordEntry = () =>
const PasswordEntry = Widget.Entry({
  placeholderText: 'Password',
  visibility: false,
  setup: (self) =>
    Utils.idle(() => {
      console.log('focus me');
      // self.grab_focus();
    }),
  // onAccept: () => handle_input().catch(logError),
}); // .on('realize', (entry) => entry.grabFocus());

const LoginBox = () =>
  Widget.Box({
    setup: (self) => {
      console.log('here');
    },
    on_focus_enter: () => {
      console.log('hi');
    },
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
              children: [UsernameField, Widget.Separator(), PasswordEntry],
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

const Greeter = () =>
  Widget.Window({
    name: 'greeter',
    keymode: 'on-demand', // TODO: exclusive
    cssClasses: ['base'],
    child: Widget.Box({
      vertical: true,
      children: [LoginBox()],
    }),
  });

App.config({
  // icons: './assets',
  style: `${App.configDir}/assets/css/style.css`,
  windows: () => [Greeter()],
});

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
