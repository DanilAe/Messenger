
var lastUsr = ""

function login_in(usrName_)
{
    m_sock.usrName = usrName_
    msgView.statusText = "You are logined as " + usrName_
}

function send(data)
{
    var date = new Date()
    if(m_sock.usrName == "")
    {
        login_in(data)
        return
    }
    var msg = {
        "usrName": m_sock.usrName,
        "msgText": data,
        "msgDate": date.toLocaleString(""),
    }
    var m_data = JSON.stringify(msg)

    if(m_sock.ipAddr != "127.0.0.1")
    {

        m_sock.addMessage(m_sock.ipAddr, m_data)
        m_sock.sendData(m_data)
        if(!rContainsIp(m_sock.ipAddr))
        {
            msgView.listModelR.append({
                                "usrName": "Unkown",
                                "msgText": aToShort(data),
                                "ip": m_sock.ipAddr,
                                "chatId": last() === undefined ? chat + 1 : last().chatId + 1
                              })
        }
        add("You(" + m_sock.usrName + ")", data, date.toLocaleString(""))
    }
    else
    {
        m_sock.addMessage(m_sock.ipAddr, m_data)
        if(!rContainsIp(m_sock.ipAddr))
        {
            msgView.listModelR.append({
                                "usrName": "Local Storage",
                                "msgText": aToShort(data),
                                "ip": m_sock.ipAddr,
                                "chatId": last() === undefined ? chat + 1 : last().chatId + 1
                              })
        }
        changeChat(last() === undefined ? chat + 1 : last().chatId + 1, "127.0.0.1", "Local Storage")
        add("You(" + m_sock.usrName + ")", data, date.toLocaleDateString(""))
    }
}

function last()
{
    return msgView.listModelR.get(msgView.listModelR.count - 1)
}

function add(usrName, msgText, msgDate)
{
    if(usrName === lastUsr || usrName === "You(" + m_sock.usrName + ")")
    {
        if(usrName !== "You(" + m_sock.usrName + ")")
            msgView.usrNameText = usrName
        var el = {
            "usrName": usrName,
            "msgText": msgText,
            "msgDate": msgDate,
        }
        msgView.listModel.append(el)
    }
    for(var i = 0; i < msgView.listModelR.count; i++)
    {
        if(msgView.listModelR.get(i).ip === m_sock.ipAddr && msgView.listModelR.get(i).usrName !== "Local Storage")
        {
            if(usrName !== "You(" + m_sock.usrName + ")")
                msgView.listModelR.get(i).usrName = usrName
            msgView.listModelR.get(i).msgText = aToShort(msgText)
            return
        }
    }
}

function aToShort(data)
{
    var mt = "" + data
    var atext = ""
    if(mt.length > 14)
    {
        for(var j = 0; j < 8; j++)
        {
            atext += mt[j]
        }
        return atext + "..."
    }
    else
        return mt
}

function rContains(chatId)
{
    for(var j = 0; j < msgView.listModelR.count; j++)
    {
        if(msgView.listModelR.get(j).chatId === chatId)
            return true
    }
    return false
}

function rContainsIp(ipAddr)
{
    for(var j = 0; j < msgView.listModelR.count; j++)
    {
        if(msgView.listModelR.get(j).ip === ipAddr)
            return true
    }
    return false
}

function changeChat(chatId, ip, usrName)
{
    if(m_sock.ipAddr === ip)
        return
    chat = chatId
    m_sock.ipAddr = ip
    lastUsr = usrName
    m_sock.getMessages(ip)
}

function newMessage(usrName, msgText, msgDate,ipAddress)
{
    if(lastUsr == "" || lastUsr == "Unkown")
    {
        if(last() !== undefined)
            changeChat(last().chatId,
                          last().ip,
                          last().usrName)
        lastUsr = usrName
        add(usrName, msgText, msgDate)
        for(var i = 0; i < msgView.listModelR.count; i++)
        {
            if(msgView.listModelR.get(i).chatId === chat)
            {
                msgView.listModelR.get(i).ip = ipAddress
            }
        }
    }
    else
        add(usrName, msgText, msgDate)
}

