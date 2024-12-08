import { jsx as _jsx, jsxs as _jsxs } from "/home/caubut/.local/share/ags/gtk3/jsx-runtime";
import Apps from "gi://AstalApps";
import { App, Astal, Gdk, Gtk } from "astal/gtk3";
import { Variable } from "astal";
const MAX_ITEMS = 8;
function hide() {
    App.get_window("launcher").hide();
}
function AppButton({ app }) {
    return _jsx("button", { className: "AppButton", onClicked: () => { hide(); app.launch(); }, children: _jsxs("box", { children: [_jsx("icon", { icon: app.iconName }), _jsxs("box", { valign: Gtk.Align.CENTER, vertical: true, children: [_jsx("label", { className: "name", truncate: true, xalign: 0, label: app.name }), app.description && _jsx("label", { className: "description", wrap: true, xalign: 0, label: app.description })] })] }) });
}
export default function Applauncher() {
    const { CENTER } = Gtk.Align;
    const apps = new Apps.Apps();
    const text = Variable("");
    const list = text(text => apps.fuzzy_query(text).slice(0, MAX_ITEMS));
    const onEnter = () => {
        apps.fuzzy_query(text.get())?.[0].launch();
        hide();
    };
    return _jsx("window", { setup: (self) => {
            self.hide();
        }, name: "launcher", anchor: Astal.WindowAnchor.TOP | Astal.WindowAnchor.BOTTOM, exclusivity: Astal.Exclusivity.IGNORE, keymode: Astal.Keymode.ON_DEMAND, application: App, onShow: () => text.set(""), onKeyPressEvent: function (self, event) {
            if (event.get_keyval()[1] === Gdk.KEY_Escape)
                self.hide();
        }, onDeleteEvent: (self) => {
            self.hide();
            return true;
        }, children: _jsxs("box", { children: [_jsx("eventbox", { widthRequest: 4000, expand: true, onClick: hide }), _jsxs("box", { hexpand: false, vertical: true, children: [_jsx("eventbox", { heightRequest: 100, onClick: hide }), _jsxs("box", { widthRequest: 500, className: "Applauncher", vertical: true, children: [_jsx("entry", { placeholderText: "Search", text: text(), onChanged: self => text.set(self.text), onActivate: onEnter }), _jsx("box", { spacing: 6, vertical: true, children: list.as(list => list.map(app => (_jsx(AppButton, { app: app })))) }), _jsxs("box", { halign: CENTER, className: "not-found", vertical: true, visible: list.as(l => l.length === 0), children: [_jsx("icon", { icon: "system-search-symbolic" }), _jsx("label", { label: "No match found" })] })] }), _jsx("eventbox", { expand: true, onClick: hide })] }), _jsx("eventbox", { widthRequest: 4000, expand: true, onClick: hide })] }) });
}
//# sourceMappingURL=AppLauncher.js.map