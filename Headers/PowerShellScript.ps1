
Param([string]$att,[string]$subj,[string]$body)

Function sendEmail
        {

            Param(
                    [Parameter(`
                    Mandatory=$true)]
                    [string] $To,
                    [Parameter(`
                    Mandatory=$true)]
                    [string]$From,
                    [Parameter(`
                    Mandatory=$true)]
                    [string]$Password,
                    [Parameter(`
                    Mandatory=$true)]
                    [string]$subject,
                    [Parameter(`
                    Mandatory=$true)]
                    [string]$Body,
                    [Parameter(`
                    Mandatory=$trye)]
                    [string]=$attachment
            )
try{
                        $Msg= New-Object System.Net.Mail.MailMessage($From,$To,$Subject,$Body)
                        $Srv="Smtp.gmail.com"
                                if($attachment -ne $null){
                                try{
                                    $attachment=$attachment -split("\:\:");
                                    ForEach($val in $Attachments)
                                    {
                                        $attach= New-Object System.Net.Mail.Attachment($val)
                                                $Msg.Attachments.Add($attach)
                                    }
                                    catch{
                                        exit 2;
                                    }
                                $Client = new-object net.Mail.SmtpClient($Srv,587)
                                            $Client.EnableSsl=$true
                                            $Client.Credentials= New-Object System.Net.NetworkCredential($From.Split("@")[0],$Password)
                                            $Client.send($Msg)
                                                    Remove-Variable -Name Client
                                    Remove-Variable -Name Password
                                    exit 7;
                                }

                        }
                    }
                    catch{
                        exit 3;
                    }
        }

try{
    Send-Email
    -attachment $Att
    -To "Address of the recepit"
    -Body $Body
    -Subject $Subj
    -Password "Tralalala"
    -From "Address of the sender"
}
catch{
    exit 4;
}

