class Debugging
{
	[NonSerialized()]
	string m_FileName;
	
    bool JM_CF_Mods;
	bool JM_CF_RPC;
	bool JM_CF_Credits;
	
	private void Debugging()
	{
		m_FileName = "$profile:Debugging.json";
	}
	
	void Log( string text, string type )
	{
		bool printOut = false;
		
		int success = EnScript.GetClassVar( this, type, 0, printOut );
		
		if ( success != 0 && printOut )
		{
			Print( "" + text );
		}
	}
	
	static ref Debugging Load()
	{
		ref Debugging settings = new Debugging();

		if ( FileExist( m_FileName ) )
		{
			JsonFileLoader<Debugging>.JsonLoadFile( m_FileName, settings );
		} else {
			settings.Defaults();
			settings.Save();
		}

		return settings;
	}

	void Save()
	{
		JsonFileLoader<Debugging>.JsonSaveFile( m_FileName, this );
	}
	
	void Defaults()
	{
		// TODO: Change to false
	    JM_CF_Mods = true;
		JM_CF_RPC = true;
		JM_CF_Credits = true;
	}
}

static ref Debugging g_Debugging;

static ref Debugging GetDebugging()
{
    if ( !g_Debugging )
    {
        g_Debugging = Debugging.Load();
    }

    return g_Debugging;
}