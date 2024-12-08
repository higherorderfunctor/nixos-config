import { App } from "astal/gtk3";
import style from "./style.scss";
import AppLauncher from "./widget/AppLauncher.tsx";
App.start({
    instanceName: "launcher",
    css: style,
    main: AppLauncher,
});
//# sourceMappingURL=index.js.map