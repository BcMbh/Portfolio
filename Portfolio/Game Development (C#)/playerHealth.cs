using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class playerHealth : MonoBehaviour
{
	private RespawnController Respawn;
	private Lifes Life;
	public GameObject deathEffect;

    public int health = 100;
	public int currentHealth;
	public int regenAmount;
	public int regenRate;
	public int regenTime;

	private bool immune = false;
	public int respawnTime;

	void Start()
	{
		Life = this.GetComponent<Lifes>();
		currentHealth = health;
		InvokeRepeating("Regenerate", regenTime, regenRate);
	}

	public void TakeDamage(int damage)
	{
		if(immune == false){
			currentHealth -= damage;
		}

		/*StartCoroutine(DamageAnimation());*/

		if(currentHealth <= 0)
		{
			immune = true;
			Die();
		}
	}

	void Regenerate() 
	{
     	if(currentHealth < health){
        	currentHealth += regenAmount;
 		}
	}	 

	void Die()
	{	
		this.gameObject.SetActive(false);

		Life.lifes -= 1;

		Invoke("respawn",respawnTime);

		/*SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex);**/
	}

	void respawn()
	{
		if(Life.lifes == 0){
			Respawn = GameObject.FindGameObjectWithTag("Respawn").GetComponent<RespawnController>();
			transform.position = Respawn.lastCheckpointPos;
			Life.lifes = Life.maxLifes;
		}

		this.gameObject.SetActive(true);
		currentHealth = health;
		immune = false;
	}

	/*IEnumerator DamageAnimation()
	{
		SpriteRenderer[] srs = GetComponentsInChildren<SpriteRenderer>();

		for (int i = 0; i < 3; i++)
		{
			foreach (SpriteRenderer sr in srs)
			{
				Color c = sr.color;
				c.a = 0;
				sr.color = c;
			}

			yield return new WaitForSeconds(.1f);

			foreach (SpriteRenderer sr in srs)
			{
				Color c = sr.color;
				c.a = 1;
				sr.color = c;
			}

			yield return new WaitForSeconds(.1f);
		}
	}*/

}
